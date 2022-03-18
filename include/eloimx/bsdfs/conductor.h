#pragma once
#include <eloimx/eloimx.h>
#include <eloimx/render/bsdf.h>
#include <unordered_map>
ELX_NAMESPACE_BEGIN

class elxConductor : public elxBSDF {
    
    elxTexture *m_specularReflectance;
    elxSpectrum m_eta;
    elxSpectrum m_k;

    elxConductor() { }
protected:
    static std::unordered_map<std::string, elxSpectrum> etaMap, kMap;

    Vec3f reflect(const Vec3f &wi) const;

public:
    elxConductor(elxTexture *reflectance, std::string metal);

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const;

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const;

    virtual elxSpectrum eval(const elxBSDFSamplingRecord &bRec) const;

    virtual float pdf(const elxBSDFSamplingRecord &bRec) const;

    virtual std::string toString() const;
};
ELX_NAMESPACE_END