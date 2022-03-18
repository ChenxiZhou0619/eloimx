#pragma once
#include <eloimx/eloimx.h>
#include <eloimx/render/bsdf.h>

ELX_NAMESPACE_BEGIN

class elxMirror : public elxBSDF {
    elxTexture *m_specularReflectance;

    elxMirror() { }
protected:
    Vec3f reflect(const Vec3f &wi) const;

public:
    elxMirror(elxTexture *specularReflectance) : m_specularReflectance(specularReflectance) { }

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const;

    virtual elxSpectrum sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const;

    virtual elxSpectrum eval(const elxBSDFSamplingRecord &bRec) const;

    virtual float pdf(const elxBSDFSamplingRecord &bRec) const;

    virtual std::string toString() const;

};

ELX_NAMESPACE_END