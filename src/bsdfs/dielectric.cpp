#include <eloimx/bsdfs/dielectric.h>
#include <eloimx/core/util.h>
// {2} material

ELX_NAMESPACE_BEGIN
Vec3f elxDielectric::reflect(const Vec3f &wi) const {
    return Vec3f(-wi.x, wi.y, -wi.z);
}

Vec3f elxDielectric::refract(const Vec3f &wi, float cosThetaT) const {
    float scale = -(cosThetaT < 0 ? (1.0f/m_eta) : m_eta);
    return Vec3f(scale * wi.x, cosThetaT, scale * wi.z); 
}


// todo
elxSpectrum elxDielectric::sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const {
    std::cout<<"This should not be executed, Dielectric::sample function\n";
    if (elxFrame::cosTheta(bRec.wi) <= 0){
        return elxSpectrum(.0f);
    }
    //bRec.wo
    return elxSpectrum(.0f);
}

elxSpectrum elxDielectric::sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const {
    float cosThetaT;
    float F = fresnelDieletricExt(elxFrame::cosTheta(bRec.wi), cosThetaT, m_eta);

    if (sample.x <= F) {

        bRec.wo = reflect(bRec.wi);
        /*
        std::cout<<"------------------- Reflect! --------------------------\n";
        std::cout<<"bRec.wi = ("<<bRec.wi.x<<", "<<bRec.wi.y<<", "<<bRec.wi.z<<"\n";
        std::cout<<"bRec.wo = ("<<bRec.wo.x<<", "<<bRec.wo.y<<", "<<bRec.wo.z<<"\n";
        */
        bRec.eta = 1.f;
        pdf = F;

        return m_specularReflectance->eval(*bRec.itsPtr, true);
    } else {

        bRec.wo = refract(bRec.wi, cosThetaT);
        /*
        std::cout<<"------------------- Refract! --------------------------\n";
        std::cout<<"bRec.wi = ("<<bRec.wi.x<<", "<<bRec.wi.y<<", "<<bRec.wi.z<<"\n";
        std::cout<<"bRec.wo = ("<<bRec.wo.x<<", "<<bRec.wo.y<<", "<<bRec.wo.z<<"\n";
        */
        bRec.eta = (cosThetaT < 0) ? m_eta : (1.0f/m_eta);
        pdf = 1- F;

        /* Radiance must be scaled to account for the solid angle compression
            that occurs when corssing the interface 
            PBRT p526 */
        float factor = (cosThetaT < 0) ? (1.0f/m_eta) : m_eta;
        return m_specularTransmittance->eval(*bRec.itsPtr, true) * (factor * factor);
    }
    return elxSpectrum(.0f);
}

elxSpectrum elxDielectric::eval(const elxBSDFSamplingRecord &bRec) const {
    float cosThetaT;
    float F = fresnelDieletricExt(elxFrame::cosTheta(bRec.wi), cosThetaT, m_eta);       

    if (elxFrame::cosTheta(bRec.wi) * elxFrame::cosTheta(bRec.wo) >= 0) {
        if (std::abs(glm::dot(reflect(bRec.wi), bRec.wo)-1) > Epsilon)
            return elxSpectrum(.0f);
        return m_specularReflectance->eval(*bRec.itsPtr, true) * F;
    } else {
        if (std::abs(glm::dot(refract(bRec.wi, cosThetaT), bRec.wo)-1) > Epsilon)
            return elxSpectrum(.0f);
        
        float factor = (cosThetaT < 0) ? (1.0f/m_eta) : m_eta;
        
        return m_specularTransmittance->eval(*bRec.itsPtr, true) * factor * factor * (1 - F); 
    }
}

float elxDielectric::pdf(const elxBSDFSamplingRecord &bRec) const {
    float cosThetaT;
    float F = fresnelDieletricExt(elxFrame::cosTheta(bRec.wi), cosThetaT, m_eta);       

    if (elxFrame::cosTheta(bRec.wi) * elxFrame::cosTheta(bRec.wo) < 0) {
        // pdf of refract
        if (std::abs(glm::dot(bRec.wi, bRec.wo) - 1) > Epsilon)
            return .0f;
        return 1-F;
    }
    else {
        // pdf of reflect 
        if (std::abs(glm::dot(reflect(bRec.wi), bRec.wo)-1) > Epsilon)
            return .0f;
        return F;
    }
}

std::string elxDielectric::toString() const {
    return fmt::format("Here is a dielectric:\n specularReflectance is {}\n transmittanceReflectance is {}\n eta={}",
        m_specularReflectance->toString(),
        m_specularTransmittance->toString(),
        m_eta);
}

ELX_NAMESPACE_END