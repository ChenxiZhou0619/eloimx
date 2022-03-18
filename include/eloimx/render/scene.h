/*
    scene.h
    create: 2022.2.25
*/
#pragma once 
#include <eloimx/eloimx.h>
#include <embree3/rtcore.h>
#include <eloimx/render/shape.h>
#include <eloimx/render/intersection.h>
#include <eloimx/render/common.h>
#include <unordered_map>
#include <vector>

ELX_NAMESPACE_BEGIN
class elxScene {
    unsigned int geoCount;
    RTCScene rtcScene;
    std::unordered_map<unsigned int, Shape*> hash;
    std::vector<elxEmitter *> emitters;
public:
    elxScene(RTCDevice device):geoCount(0) {
        rtcScene = rtcNewScene(device);
    }

    void attachGeometry(Shape *elxShape) {
        rtcAttachGeometryByID(rtcScene, elxShape->shapePtr, geoCount);
        elxShape->setGeomID(geoCount);
        if (elxShape->isEmitter()) {
            /// record in the emitters
            emitters.push_back(elxShape->getEmitter());
        }
        hash[geoCount++] = elxShape;
    }

    void commitScene() {
        rtcCommitScene(rtcScene);
    }

    bool rayIntersect(const elxRay &ray, elxIntersection &its) const{
        RTCIntersectContext context;
        rtcInitIntersectContext(&context);
        
        RTCRayHit rayhit;
        rayhit.ray = ray.toRTC();
        rayhit.hit.geomID = RTC_INVALID_GEOMETRY_ID;
        rayhit.hit.instID[0] = RTC_INVALID_GEOMETRY_ID;

        rtcIntersect1(rtcScene, &context, &rayhit);
    
        if (rayhit.hit.geomID == RTC_INVALID_GEOMETRY_ID) {
            its.t = std::numeric_limits<float>::infinity();
            return false;
        } else {
            std::unordered_map<unsigned int, Shape*>::const_iterator it = hash.find(rayhit.hit.geomID);
            if (it != hash.end()) {
                its.shape = it->second;
            } else {
                std::cout<<"error, this should not appear\n";
                exit(1);
            }
            its.t = rayhit.ray.tfar;
            its.p = ray(its.t);
            Vec3f geoNormal = Vec3f(rayhit.hit.Ng_x, 
                                    rayhit.hit.Ng_y,
                                    rayhit.hit.Ng_z);
            geoNormal = its.shape->getNormal(ray, its.p, geoNormal);

            its.shFrame = its.geoFrame = elxFrame(geoNormal);
            its.wi = its.shFrame.toLocal(-ray.d);
            its.uv = its.shape->getUV(its.p);
            // no ray differentials currently
            its.haveUVPartials = false;
        }
        return true;
    }

    elxSpectrum evalEnv(const elxRay &ray) const {
        // hack: return a const value
        return elxSpectrum(.5f);
    }

    elxSpectrum sampleEmitterDirect(elxDirectSamplingRecord &dRec,
        const Point2f &_sample, bool testVisibility) const;

};

ELX_NAMESPACE_END