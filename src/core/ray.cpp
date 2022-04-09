#include <eloimx/core/ray.h>

ELX_NAMESPACE_BEGIN

elxRay::elxRay() {
    tnear = Epsilon;
    tfar  = std::numeric_limits<float>::infinity();
    time = 0;
}

elxRay::elxRay(const Point3f &org, const Vec3f &dir): o(org), d(dir) {
    normalize(d);
    tnear = Epsilon;
    tfar  = std::numeric_limits<float>::infinity();
    time = 0;
}

elxRay::elxRay(const Point3f &org, const Vec3f &dir, float tmin, float tmax):o(org), d(dir), tnear(tmin), tfar(tmax) {
    normalize(d);
    time=0;
}

Point3f elxRay::operator()(float t) const {
    return o + t * d;
}

std::string elxRay::toString() const {
    return fmt::format("Ray: origin=[{},{},{}], direction=[{},{},{}], tmin={}, tmax={}, time={}",
                            o.x, o.y, o.z, d.x, d.y, d.z, tnear, tfar, time);

}

RTCRay elxRay::toRTC() const {
    RTCRay rtcRay;
    rtcRay.org_x = o.x;
    rtcRay.org_y = o.y;
    rtcRay.org_z = o.z;

    rtcRay.dir_x = d.x;
    rtcRay.dir_y = d.y;
    rtcRay.dir_z = d.z;

    rtcRay.tnear = tnear;
    rtcRay.tfar  = tfar;

    rtcRay.mask = -1;
    rtcRay.flags = 0;

    return rtcRay;
}


ELX_NAMESPACE_END