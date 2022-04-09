#include <eloimx/render/intersection.h>
#include <fmt/format.h>
#include <eloimx/render/emitter.h>
ELX_NAMESPACE_BEGIN
std::string elxIntersection::toString() const {
    if (!isValid()) {
        return "Invalid intersection";
    }
    Vec3f normal = this->geoFrame.toWorld(Vec3f(0, 1, 0));
    return fmt::format("Intersection = [t={}, hitPoint=({}, {}, {}), wi in local=({}, {}, {}), normal in world = ({}, {}, {})]",
     t, p.x, p.y, p.z, wi.x, wi.y, wi.z, normal.x, normal.y, normal.z);
}

elxBSDF* elxIntersection::getBSDF(const elxRay &ray) const {
    if (!isValid()) {
        return nullptr;
    }
    return shape->getBSDF();
}

Vec3f elxIntersection::toLocal(const Vec3f &v) const {
    return shFrame.toLocal(v);
}

Vec3f elxIntersection::toWorld(const Vec3f &v) const {
    return shFrame.toWorld(v);
}

elxSpectrum elxIntersection::Le(const Vec3f &d) const {
    if (shape!=nullptr && shape->getEmitter() != nullptr)
        return shape->getEmitter()->eval(*this, d);
    else {
        std::cout<<"Error, no shape or emitter when call the Le\n";
        exit(1);
    }
}

ELX_NAMESPACE_END