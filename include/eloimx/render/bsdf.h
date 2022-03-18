#pragma once
#include <eloimx/eloimx.h>
#include <eloimx/render/intersection.h>
#include <eloimx/render/sampler.h>
#include <eloimx/render/texture.h>

ELX_NAMESPACE_BEGIN

struct elxBSDFSamplingRecord {
    // pointer to the underlying surface interaction
    elxIntersection *itsPtr;
    // pointer to a sampler instance 
    elxSampler *samplerPtr;
    // normalized incident/outgoing direction in local coordinates
    Vec3f wi, wo;
    // relative index of refraction in the sampled direction
    float eta;
    
    elxBSDFSamplingRecord(elxIntersection *itsPtr, elxSampler *samplerPtr):itsPtr(itsPtr), samplerPtr(samplerPtr), eta(1.0f), wi(itsPtr->wi){ }

    elxBSDFSamplingRecord(elxIntersection *itsPtr, const Vec3f &wi):itsPtr(itsPtr), wi(wi), eta(1.0f) { }

    elxBSDFSamplingRecord(elxIntersection *itsPtr, const Vec3f &wi, const Vec3f &wo):
        itsPtr(itsPtr), wi(wi), wo(wo), eta(1.0f){ }


private:
    elxBSDFSamplingRecord() { }
};

class elxBSDF {
public:
    inline bool useRayDifferentials() const {
        return false;
    }

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const = 0;

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const = 0;

    virtual elxSpectrum eval(const elxBSDFSamplingRecord &bRec) const = 0;

    virtual float pdf(const elxBSDFSamplingRecord &bRec) const = 0;

    //virtual float getEta() const;
    virtual std::string toString() const = 0;

protected:
    elxBSDF() { }
};
ELX_NAMESPACE_END