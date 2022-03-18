#pragma once
#include <eloimx/eloimx.h>
#include <eloimx/render/bsdf.h>

ELX_NAMESPACE_BEGIN
class elxDiffuse : public elxBSDF {

    elxDiffuse() : m_diffuseReflectance(nullptr) { }
protected:
    elxTexture *m_diffuseReflectance;
public:
    elxDiffuse(elxTexture *texture) : m_diffuseReflectance(texture) { }

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const;

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const;

    virtual elxSpectrum eval(const elxBSDFSamplingRecord &bRec) const;

    virtual float pdf(const elxBSDFSamplingRecord &bRec) const;

    virtual std::string toString() const;
};
ELX_NAMESPACE_END