#include <eloimx/core/warp.h>
ELX_NAMESPACE_BEGIN

float warp::squareToCosHemispherePdf(const Vec3f& d) {
    // according to pbrt, the pdf is cosTheta *S / PI
    return INV_PI * elxFrame::cosTheta(d);
}

Vec3f warp::squareToCosHemisphere(const Point2f &sample) {
    Point2f p = squareToUniformDiskConcentric(sample);
    float z = sqrtf(1.0f - p.x*p.x - p.y*p.y);

    return Vec3f(p.x, z, p.y);
}


Point2f warp::squareToUniformDiskConcentric(const Point2f &sample) {
    float r1 = sample.x * 2.0f - 1.0f;
    float r2 = sample.y * 2.0f - 1.0f;

    float phi, r;
    if (r1 == 0 && r2 == 0) {
        r = phi = 0;
    } else if (r1*r1 > r2*r2) {
        r = r1;
        phi = (PI * 0.25f) * (r2/r1);
    } else {
        r = r2;
        phi = (PI * 0.5f) - (r1/r2) * (PI * 0.25f);
    }

    float cosPhi, sinPhi;
    cosPhi = cosf(phi);
    sinPhi = sinf(phi);

    return Point2f(r * cosPhi, r * sinPhi);
}

ELX_NAMESPACE_END