#pragma once
#include <eloimx/render/texture.h>
ELX_NAMESPACE_BEGIN

/*No mipmap currently */
class elxBitMap : public elxTexture {
protected:
    unsigned char *m_colorMap;
    int m_width, m_height, m_channels;

    elxBitMap() { }

public:
    elxBitMap(std::string &filepath);

    virtual elxSpectrum eval(const elxIntersection &its, bool filter) const;

    virtual elxSpectrum eval(const Point2f &uv) const;

    virtual elxSpectrum eval(const Point2f &uv, const Vec2f &d0, const Vec2f &d1) const;

    virtual bool useRayDifferentials() const;

    virtual std::string toString() const;

    virtual ~elxBitMap();
};

ELX_NAMESPACE_END