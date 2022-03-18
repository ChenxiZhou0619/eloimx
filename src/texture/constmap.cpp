#include <eloimx/texture/constmap.h>
#include <eloimx/render/intersection.h>
ELX_NAMESPACE_BEGIN

elxSpectrum elxConstMap::eval(const elxIntersection &its, bool filter) const {
    return m_color;
}

elxSpectrum elxConstMap::eval(const Point2f &uv) const {
    std::cout<<"Should not be accessed, cause no need to implement this\n";
    exit(1);
}

elxSpectrum elxConstMap::eval(const Point2f &uv, const Vec2f &d0, const Vec2f &d1) const {
    std::cout<<"This should not be accessed cause no need to implement this\n";
    exit(1);
}

// no need for this texture use ray differentials
bool elxConstMap::useRayDifferentials() const {
    return false;
}

std::string elxConstMap::toString() const {
    return fmt::format("Const texture:\n color is [{}, {}, {}]",
        m_color.r, m_color.g, m_color.b);
}

ELX_NAMESPACE_END