#pragma once
#include <eloimx/render/texture.h>
ELX_NAMESPACE_BEGIN

class elxConstMap : public elxTexture {
protected:
    elxSpectrum m_color;
    elxConstMap() { }
public:
    elxConstMap(const elxSpectrum &spc) : m_color(spc) { }

    virtual elxSpectrum eval(const elxIntersection &its, bool filter) const;

    virtual elxSpectrum eval(const Point2f &uv) const;

    virtual elxSpectrum eval(const Point2f &uv, const Vec2f &d0, const Vec2f &d1) const;

    virtual bool useRayDifferentials() const;

    virtual std::string toString() const;

};

ELX_NAMESPACE_END