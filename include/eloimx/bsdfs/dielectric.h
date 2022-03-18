#pragma once
#include <eloimx/eloimx.h>
#include <eloimx/render/bsdf.h>

ELX_NAMESPACE_BEGIN

class elxDielectric : public elxBSDF {
    elxTexture *m_specularReflectance;
    elxTexture *m_specularTransmittance;
    
    float m_eta;

    elxDielectric() { }

protected:

    Vec3f reflect(const Vec3f &wi) const;

    Vec3f refract(const Vec3f &wi, float cosThetaT) const;
public:
    elxDielectric(elxTexture *reflectance, 
        elxTexture *transmittance,
        float eta) : 
        m_specularReflectance(reflectance), m_specularTransmittance(transmittance), m_eta(eta) { }

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const;

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const;

    virtual elxSpectrum eval(const elxBSDFSamplingRecord &bRec) const;

    virtual float pdf(const elxBSDFSamplingRecord &bRec) const;

    virtual std::string toString() const;
};

ELX_NAMESPACE_END