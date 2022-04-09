#include <eloimx/core/frame.h>

ELX_NAMESPACE_BEGIN

elxFrame::elxFrame(const Vec3f &normal){
    Yprime = normal;
    normalize(Yprime);
    Xprime = glm::cross(Yprime, Vec3f(1,0,0));
    normalize(Xprime);
    if (vecLen(Xprime) <= Epsilon)
        Xprime = glm::cross(Yprime, Vec3f(0,1,0));
    else {
        
    }
    Zprime = glm::cross(Xprime, Yprime);
}

Vec3f elxFrame::toLocal(const Vec3f &v) const {
    return Vec3f(
        glm::dot(Xprime, v),
        glm::dot(Yprime, v),
        glm::dot(Zprime, v)
    );
}

Vec3f elxFrame::toWorld(const Vec3f &v) const  {
    return v.x * Xprime + v.y * Yprime + v.z * Zprime;
}

float elxFrame::cosTheta(const Vec3f &v) {
    return v.y;
}

float elxFrame::cosTheta2(const Vec3f &v) {
    return v.y * v.y;
}

float elxFrame::sinTheta(const Vec3f &v) {
    return sqrt(1 - v.y * v.y);
}

std::string elxFrame::toString() const {
    return fmt::format("Frame = Xprime = [{}, {}, {}], Yprime = [{}, {}, {}],  Zprime = [{}, {}, {}]",
    Xprime.x, Xprime.y, Xprime.z,
    Yprime.x, Yprime.y, Yprime.z,
    Zprime.x, Zprime.y, Zprime.z);
}

ELX_NAMESPACE_END