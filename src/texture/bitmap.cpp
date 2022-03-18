#include <eloimx/texture/bitmap.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <eloimx/render/intersection.h>

ELX_NAMESPACE_BEGIN

elxBitMap::elxBitMap(std::string &filepath){
    m_colorMap = stbi_load(
        filepath.c_str(), 
        &m_width,
        &m_height,
        &m_channels,
        0);
    if (!m_colorMap){
        std::cout<<"Error when read the file\n";
        exit(1);
    }
    else if (m_channels != 3) {
        std::cout<<"Unsupported image type --channels != 3\n";
        exit(1);
    } 
}

elxBitMap::~elxBitMap() {
    delete m_colorMap;
}

elxSpectrum elxBitMap::eval(const elxIntersection &its, bool filter) const {
    Point2f uv = its.uv;
    if (its.haveUVPartials && filter) {
        return eval(
            uv, 
            Vec2f(its.dudx, its.dudy),
            Vec2f(its.dvdx, its.dvdy));
    } else {
        return eval(uv);
    }
}

elxSpectrum elxBitMap::eval(const Point2f &uv) const {
    int pixelU = uv.x * (m_width - 1),
        pixelV = uv.y * (m_height - 1);
    float r = float(m_colorMap[pixelV * m_width * 3 + pixelU * 3]     / 255.f),
          g = float(m_colorMap[pixelV * m_width * 3 + pixelU * 3 + 1] / 255.f),
          b = float(m_colorMap[pixelV * m_width * 3 + pixelU * 3 + 2] / 255.f);
    return elxSpectrum(r, g, b);
}

elxSpectrum elxBitMap::eval(const Point2f &uv, const Vec2f &d0, const Vec2f &d1) const {
    std::cout<<"This should not be accessed cause this function has not benn implemented yet\n";
    exit(1);
}

// currently not support raydifferentials
bool elxBitMap::useRayDifferentials() const {
    return false;
}

std::string elxBitMap::toString() const {
    return fmt::format("Bitmap texture:\n width={}, height={}, channels={}",
        m_width, m_height, m_channels);
}

ELX_NAMESPACE_END