#pragma once
#include <eloimx/eloimx.h>

ELX_NAMESPACE_BEGIN

struct elxIntersection;

class elxTexture {
public:
    virtual elxSpectrum eval(const elxIntersection &its, bool filter) const=0;

    virtual elxSpectrum eval(const Point2f &uv) const=0;

    virtual elxSpectrum eval(const Point2f &uv, const Vec2f &d0, const Vec2f &d1) const=0;

    virtual bool useRayDifferentials() const=0;

        virtual std::string toString() const=0;

    virtual ~elxTexture() { }
};

ELX_NAMESPACE_END