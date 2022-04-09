#include <eloimx/core/math.h>
ELX_NAMESPACE_BEGIN
void normalize(Vec3f &v) {
    if (vecLen(v) < Epsilon){
        v = Vec3f(.0f);
        return;
    }
    float invL = 1.0f / vecLen(v);
    v *= invL;
}

float vecLen(const Vec3f &v) {
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);

}
ELX_NAMESPACE_END