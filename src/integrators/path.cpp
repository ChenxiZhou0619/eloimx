/*
    path.cpp
    create: 2022.3.3
*/
#include <eloimx/integrators/path.h>
#include <eloimx/render/bsdf.h>
#include <eloimx/render/common.h>
#include <algorithm>

ELX_NAMESPACE_BEGIN
float elxPathTracer::miWeight(float pdfA, float pdfB) const {
    pdfA *= pdfA;
    pdfB *= pdfB;
    return pdfA / (pdfA + pdfB);
}

elxSpectrum elxPathTracer::Li(const elxRay &r, 
        elxRadianceQueryRecord &rRec) const {
    
    /*Some local variables*/
    const elxScene *scene = rRec.scene;
    elxIntersection &its = rRec.its;
    elxRay ray(r);
    elxSpectrum Li(.0f);
    bool scattered = false;
    elxSampler *sampler = rRec.sampler;
    
    /*Perform the first ray intersection*/
    rRec.rayIntersect(ray);
    ray.tnear = Epsilon;

    elxSpectrum throughput(1.0f);
    float eta = 1.0f;

    while(rRec.depth <= m_maxDepth || m_maxDepth <0) {
        // m_maxDepth<0 means positive infinity
        if (!its.isValid()) {
            // probabily hit the environment
            Li += throughput * scene->evalEnv(ray);
            break;
        }

        // else hit the surface, compute the bsdf
        const elxBSDF *bsdf = its.getBSDF(ray);

        // if hit the emitter
        if (its.isEmitter() && (!m_hideEmitters || scattered)) { 
            //std::cout<<"hit emitter\n";
            Li += throughput * its.Le(-ray.d);
            return Li;
        }
        // if hit the subface scattering
        // ignore now

        // end the tracing if
        // 1. path length exceeds the specifed maximum
        // 2. encounter the light leak

        if ((rRec.depth >= m_maxDepth && m_maxDepth > 0)
            || (m_strictNormals && dot(ray.d, its.geoFrame.Yprime)*elxFrame::cosTheta(its.wi) >= 0)) {
            /*
            std::cout<<"Break up to conflict between shFrame and geoFrame\n";
            std::cout<<"The ray : "<<ray.toString()<<"\n";
            std::cout<<"The frame : "<<its.geoFrame.toString()<<"\n";
            */
            break;
        }
        if (bsdf == nullptr) {
            std::cout<<"Its surface has no bsdf\n";
            exit(1);
        } 
        /*------------ Direct illumination sampling ------------------------*/
        /*------------ Skip right know--------------------------------------*/
        elxDirectSamplingRecord dRec(its);
        elxSpectrum value = scene->sampleEmitterDirect(dRec, sampler->sample2D(), true);     
        if (!value.isZero()) {
            elxBSDFSamplingRecord bRec(&its, its.toLocal(dRec.d));
            // evaluate the BSDF * cos(theta)
            elxSpectrum bsdfVal = bsdf->eval(bRec);
            // prevent light leak
            //std::cout<< bsdfVal.toString() <<"\n";
            if (!bsdfVal.isZero() && glm::dot(dRec.d, its.geoFrame.Yprime)*elxFrame::cosTheta(bRec.wo) > 0) {
                // caculate the multiple important sampling
                float bsdfPdf = bsdf->pdf(bRec);

                float weight = miWeight(dRec.pdf, bsdfPdf);
                Li += throughput * value * bsdfVal * weight;

            }
        }
        
        /*-----------------  BSDF sampling --------------------------------*/
        float bsdfPdf;
        elxBSDFSamplingRecord bRec(&its, rRec.sampler);
        elxSpectrum bsdfWeight = bsdf->sample(bRec, rRec.sampler->sample2D(), bsdfPdf);
        if (bsdfWeight.isZero())
            break;
        // hack, might be changed afterwards
        scattered = true;

        Vec3f wo = its.toWorld(bRec.wo);
        float woDotGeoN = glm::dot(its.geoFrame.Yprime, wo);
        if(m_strictNormals && woDotGeoN * elxFrame::cosTheta(bRec.wo) <= 0){
            //std::cout<<"wo : ("<<bRec.wo.x<<", "<<bRec.wo.y<<", "<<bRec.wo.z<<")\n";
            //std::cout<<"break up to light leak\n";
            break;
        }

        bool hitEmitter = false;
        elxSpectrum value_;

        ray = elxRay(its.p, wo);
        if (scene->rayIntersect(ray, its)) {
            if (its.isEmitter()) {
                value_ = its.Le(-ray.d);
                hitEmitter = true;
            }
        } else {
            /*intersect nothing*/
            value_ = scene->evalEnv(ray);
            hitEmitter = true;
        }

        throughput *= bsdfWeight;
        eta *= bRec.eta;
        
        if (hitEmitter) {
            // terminated the tracing
            Li += throughput * value_ ;//* bsdfPdf;
        }
        
        /*----------------- indirect illumination ------------------*/
        if (!its.isValid()) break;
        rRec.depth++;
        // don't understand
        /*
        if (rRec.depth++ >= m_rrDepth) {
            float q = std::min(throughput.max() * eta * eta,  0.95f);
            if (rRec.sampler->sample1D() >= q)
                break;
        }*/
    }
    return Li;
}


ELX_NAMESPACE_END