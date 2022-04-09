#include <eloimx/render/shape.h>
#include <eloimx/render/emitter.h>
#include <eloimx/render/bsdf.h>
#include <eloimx/render/common.h>
ELX_NAMESPACE_BEGIN

void Shape::boundEmitter(elxEmitter *emitter){
    this->emitter = emitter;
    emitter->m_shape = this;
}

elxTriangle::elxTriangle(RTCDevice device,
                 const Point3f &p1,
                 const Point3f &p2,
                 const Point3f &p3) {
        shapePtr = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);

        float *vertices = (float *) rtcSetNewGeometryBuffer(
            shapePtr,
            RTC_BUFFER_TYPE_VERTEX,
            0,
            RTC_FORMAT_FLOAT3,
            3*sizeof(float),
            3
        );

        unsigned *indices = (unsigned *)rtcSetNewGeometryBuffer(
            shapePtr,
            RTC_BUFFER_TYPE_INDEX,
            0,
            RTC_FORMAT_UINT3,
            3*sizeof(unsigned),
            1
        );

        if (vertices && indices) {
            vertices[0] = p1.x; vertices[1] = p1.y; vertices[2] = p1.z;
            vertices[3] = p2.x; vertices[4] = p2.y; vertices[5] = p2.z;
            vertices[6] = p3.x; vertices[7] = p3.y; vertices[8] = p3.z; 

            indices[0] = 0; indices[1] = 1; indices[2] = 2;
        }

        rtcCommitGeometry(shapePtr);

        emitter = nullptr;
        bsdf    = nullptr;
        geomID  = RTC_INVALID_GEOMETRY_ID;
}

void elxTriangle::samplePosition(elxDirectSamplingRecord &dRec, const Point2f &sample) const {
    // uniformly sample a point on the rectangle
    Point2f uv = sample;
    if(uv.x + uv.y > 1) {
        uv.x = 1 - uv.x;
        uv.y = 1 - uv.y;
    }
    float* vertices = (float *)rtcGetGeometryBufferData(shapePtr, RTC_BUFFER_TYPE_VERTEX, 0);
    Point3f vertex(vertices[0], vertices[1], vertices[2]);
    Vec3f v1(vertices[3]-vertices[0], vertices[4]-vertices[1], vertices[5]-vertices[2]);
    Vec3f v2(vertices[6]-vertices[0], vertices[7]-vertices[1], vertices[8]-vertices[2]);
    
    dRec.p = vertex + uv.x * v1 + uv.y * v2;
    dRec.n = normalize(glm::cross(v1, v2));
    dRec.pdf = 1.0f / area();
}

void elxTriangle::sampleDirect(elxDirectSamplingRecord &dRec, const Point2f &sample) const{
    samplePosition(dRec, sample);
    dRec.d = dRec.p - dRec.ref;
    dRec.dist = vecLen(dRec.d);
    dRec.d /= dRec.dist;
    float dp = glm::dot(dRec.d, dRec.n);
    // flip the sample point normal
    if (dp > 0) {
        dRec.n = -dRec.n;
    }
    
    dRec.pdf *= (dp != 0)? (dRec.dist*dRec.dist / std::abs(dp)) : .0f;
}

float elxTriangle::area() const {

    float* vertices = (float *)rtcGetGeometryBufferData(shapePtr, RTC_BUFFER_TYPE_VERTEX, 0);

    Vec3f v1(vertices[3]-vertices[0], vertices[4]-vertices[1], vertices[5]-vertices[2]);
    Vec3f v2(vertices[6]-vertices[0], vertices[7]-vertices[1], vertices[8]-vertices[2]);

    return 0.5f * vecLen(glm::cross(v1, v2));    
}

Vec3f elxTriangle::getNormal(const elxRay &ray, const Point3f &hit, const Vec3f &nDir) const {
    // two side shape
    // just make the normal and wi in the same side
    if (glm::dot(ray.d, nDir) > 0)
        return -nDir;
    else return nDir;
}

Point2f elxTriangle::getUV(const Point3f &hit) const {
    std::cout<<"Triangle has not implemented the getUV\n";
    return Point2f(.0f);
} 

std::string elxTriangle::toString() const {
    float* vertices = (float *)rtcGetGeometryBufferData(shapePtr, RTC_BUFFER_TYPE_VERTEX, 0);
    std::string bsdfDes     = (bsdf==nullptr)?"No bsdf":bsdf->toString();
    std::string emitterDes  = (emitter==nullptr)?"No emitter":emitter->toString(); 
    return fmt::format("Shape is Triangle, address:{} \nits vertices:[\n\t({}, {}, {})\n\t({}, {}, {})\n\t({}, {}, {})\n]\nits bsdf: {}\nits emitter: {}",
        (void *)this,
        vertices[0], vertices[1], vertices[2],
        vertices[3], vertices[4], vertices[5],
        vertices[6], vertices[7], vertices[8],
        bsdfDes,
        emitterDes);
}

elxRectangle::elxRectangle(RTCDevice device,
                const Point3f &p1,
                const Point3f &p2,
                const Point3f &p3,
                const Point3f &p4){
    shapePtr = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);
    
    float *vertices = (float *) rtcSetNewGeometryBuffer(
        shapePtr,
        RTC_BUFFER_TYPE_VERTEX,
        0,
        RTC_FORMAT_FLOAT3,
        3*sizeof(float),
        4
    );

    unsigned *indices = (unsigned *)rtcSetNewGeometryBuffer(
        shapePtr,
        RTC_BUFFER_TYPE_INDEX,
        0,
        RTC_FORMAT_UINT3,
        3*sizeof(unsigned),
        2
    );

    if (vertices && indices) {
        vertices[0] = p1.x; vertices[1] = p1.y; vertices[2] = p1.z;
        vertices[3] = p2.x; vertices[4] = p2.y; vertices[5] = p2.z;
        vertices[6] = p3.x; vertices[7] = p3.y; vertices[8] = p3.z; 
        vertices[9] = p4.x; vertices[10]= p4.y; vertices[11]= p4.z;

        indices[0] = 0; indices[1] = 2; indices[2] = 1;
        indices[3] = 0; indices[4] = 2; indices[5] = 3;
    }

    rtcCommitGeometry(shapePtr);

    emitter = nullptr;
    bsdf    = nullptr;
    geomID  = RTC_INVALID_GEOMETRY_ID;
}

void elxRectangle::samplePosition(elxDirectSamplingRecord &dRec, const Point2f &sample) const {
    Point2f uv = sample;
    float *vertices = (float *)rtcGetGeometryBufferData(shapePtr, RTC_BUFFER_TYPE_VERTEX, 0);
    Point3f vertex(vertices[0], vertices[1], vertices[2]);
    Vec3f v1(vertices[3]-vertices[0], vertices[4]-vertices[1], vertices[5]-vertices[2]);
    Vec3f v2(vertices[9]-vertices[0], vertices[10]-vertices[1], vertices[11]-vertices[2]);

    dRec.p = vertex + uv.x * v1 + uv.y * v2;
    dRec.n = normalize(glm::cross(v1, v2));
    dRec.pdf = 1.0f / area();
}

float elxRectangle::area() const {
    float *vertices = (float *)(float *)rtcGetGeometryBufferData(shapePtr, RTC_BUFFER_TYPE_VERTEX, 0);
    Vec3f v1(vertices[3]-vertices[0], vertices[4]-vertices[1], vertices[5]-vertices[2]);
    Vec3f v2(vertices[9]-vertices[0], vertices[10]-vertices[1], vertices[11]-vertices[2]);
    return vecLen(glm::cross(v1, v2));
}

void elxRectangle::sampleDirect(elxDirectSamplingRecord &dRec, const Point2f &sample) const {
    samplePosition(dRec, sample);
    dRec.d = dRec.p - dRec.ref;
    dRec.dist = vecLen(dRec.d);
    dRec.d /= dRec.dist;
    float dp = glm::dot(dRec.d, dRec.n);
    // flip the sample point normal
    if (dp > 0) {
        dRec.n = -dRec.n;
    }
    
    dRec.pdf *= (dp != 0)? (dRec.dist*dRec.dist / std::abs(dp)) : .0f;        
}

Vec3f elxRectangle::getNormal(const elxRay &ray, const Point3f &hit, const Vec3f &nDir) const {
    // two side shape
    // just make the normal and wi in the same side
    if (glm::dot(ray.d, nDir) > 0)
        return -nDir;
    else return nDir;
}   

Point2f elxRectangle::getUV(const Point3f &hit) const {
    float *vertices = (float *)rtcGetGeometryBufferData(shapePtr, RTC_BUFFER_TYPE_VERTEX, 0);
    // vertices[0],[1],[2]   -> point0
    // vertices[3],[4],[5]   -> point1
    // vertices[9],[10],[11] -> point3
    Point3f p0(vertices[0], vertices[1], vertices[2]),
            p1(vertices[3], vertices[4], vertices[5]),
            p3(vertices[9], vertices[10], vertices[11]);

    Vec3f v0 = p1 - p0,
          v1 = p3 - p0,
          p0hit = hit - p0;

    // p0hit = u * v0 + v * v1
    float v = glm::dot(p0hit, v1) / (vecLen(v1) * vecLen(v1)),
          u = glm::dot(p0hit, v0) / (vecLen(v0) * vecLen(v0));
    return Point2f(u,v);
}

std::string elxRectangle::toString() const {
    float* vertices = (float *)rtcGetGeometryBufferData(shapePtr, RTC_BUFFER_TYPE_VERTEX, 0);
    std::string bsdfDes     = (bsdf==nullptr)?"No bsdf":bsdf->toString();
    std::string emitterDes  = (emitter==nullptr)?"No emitter":emitter->toString(); 
    return fmt::format("Shape is Rectangle, address:{} \nits vertices:[\n\t({}, {}, {})\n\t({}, {}, {})\n\t({}, {}, {})\n\t({}, {}, {})\n]\nits bsdf: {}\nits emitter: {}",
        (void *)this,
        vertices[0], vertices[1], vertices[2],
        vertices[3], vertices[4], vertices[5],
        vertices[6], vertices[7], vertices[8],
        vertices[9], vertices[10], vertices[11],
        bsdfDes,
        emitterDes);
}
/*============================= user defined sphere ========================*/

void elxSphereBoundingFunc(const RTCBoundsFunctionArguments *args){
    elxSphere *sphere = (elxSphere *) (args->geometryUserPtr);
    RTCBounds *bounds_o = args->bounds_o;
    bounds_o->lower_x = sphere->center.x - sphere->radius;
    bounds_o->lower_y = sphere->center.y - sphere->radius;
    bounds_o->lower_z = sphere->center.z - sphere->radius;
    bounds_o->upper_x = sphere->center.x + sphere->radius;
    bounds_o->upper_y = sphere->center.y + sphere->radius;
    bounds_o->upper_z = sphere->center.z + sphere->radius;
}

void elxSphereIntersectFunc(const RTCIntersectFunctionNArguments *args){
    int *valid = args->valid;
    void *ptr  = args->geometryUserPtr;

    RTCRayHitN *rayhit = args->rayhit;
    RTCRayN *ray = RTCRayHitN_RayN(rayhit, 1);
    RTCHitN *hit = RTCRayHitN_HitN(rayhit, 1);
    unsigned int primID = args->primID;

    elxSphere *sphere = (elxSphere *) ptr;

    if(!valid[0]) return;

    float ray_ox = RTCRayN_org_x(ray, 1, 0),
          ray_oy = RTCRayN_org_y(ray, 1, 0),
          ray_oz = RTCRayN_org_z(ray, 1, 0),
          ray_dx = RTCRayN_dir_x(ray, 1, 0),
          ray_dy = RTCRayN_dir_y(ray, 1, 0),
          ray_dz = RTCRayN_dir_z(ray, 1, 0);

    Point3f ray_org(ray_ox, ray_oy, ray_oz);
    Vec3f   ray_dir(ray_dx, ray_dy, ray_dz);

    Vec3f v = ray_org - sphere->center;
    const float A = glm::dot(ray_dir, ray_dir);
    const float B = 2.0f * glm::dot(v, ray_dir);
    const float C = glm::dot(v, v) - sphere->radius * sphere->radius;
    const float D = B * B - 4.0f * A * C; 

    if(D < .0f) return;
    const float Q = std::sqrt(D);
    const float rcpA = 1.0f / A;
    const float t0 = 0.5f * rcpA * (-B - Q);
    const float t1 = 0.5f * rcpA * (-B + Q);
    RTCHit potentialHit;
    potentialHit.u = potentialHit.v =.0f;
    potentialHit.geomID = sphere->getGeomID();
    if ((RTCRayN_tnear(ray, 1, 0) < t0) & (t0 < RTCRayN_tfar(ray, 1, 0))) {
        int imask;
        bool mask = 1;
        {
            imask = mask ? -1 : 0;
        }

        Vec3f Ng = ray_org + t0 * ray_dir - sphere->center;
        potentialHit.Ng_x = Ng.x;
        potentialHit.Ng_y = Ng.y;
        potentialHit.Ng_z = Ng.z;

        RTCFilterFunctionNArguments fargs;
        fargs.valid = (int *)&imask;
        fargs.geometryUserPtr = ptr;
        fargs.context = args->context;
        fargs.ray = (RTCRayN *) args->rayhit;
        fargs.hit = (RTCHitN *) &potentialHit;
        fargs.N = 1;

        const float old_t = RTCRayN_tfar(ray, 1, 0);
        RTCRayN_tfar(ray, 1, 0) = t0;
        rtcFilterIntersection(args, &fargs);

        if(imask == -1){
            *((RTCHit *)hit) = potentialHit;
        } else {
            RTCRayN_tfar(ray, 1, 0) = old_t;
        }
    }
    if ((RTCRayN_tnear(ray, 1, 0) < t1) & (t1 < RTCRayN_tfar(ray, 1, 0))) {
        int imask;
        bool mask = 1;
        {
            imask = mask ? -1 : 0;
        }
         Vec3f Ng = ray_org + t1 * ray_dir - sphere->center;
        potentialHit.Ng_x = Ng.x;
        potentialHit.Ng_y = Ng.y;
        potentialHit.Ng_z = Ng.z;

        RTCFilterFunctionNArguments fargs;
        fargs.valid = (int *)&imask;
        fargs.geometryUserPtr = ptr;
        fargs.context = args->context;
        fargs.ray = (RTCRayN *) args->rayhit;
        fargs.hit = (RTCHitN *) &potentialHit;
        fargs.N = 1;

        const float old_t = RTCRayN_tfar(ray, 1, 0);
        RTCRayN_tfar(ray, 1, 0) = t1;
        rtcFilterIntersection(args, &fargs);

        if(imask == -1){
            // when in occludedFunc
            //RTCRayN_tfar(ray, 1, 0) = -std::numeric_limits<float>::infinity();
            *((RTCHit *)hit) = potentialHit;
        } else {
            RTCRayN_tfar(ray, 1, 0) = old_t;
        }
    }
}

//todo
void elxSphereOccludedFunc(const RTCOccludedFunctionNArguments *args) {
    return;
}

elxSphere::elxSphere(RTCDevice device, const Point3f &c, const float &r):center(c), radius(r) {
    shapePtr = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_USER);
    rtcSetGeometryUserPrimitiveCount(shapePtr, 1);
    rtcSetGeometryUserData(shapePtr, this);
    rtcSetGeometryBoundsFunction(shapePtr, elxSphereBoundingFunc, nullptr);
    rtcSetGeometryIntersectFunction(shapePtr, elxSphereIntersectFunc);
    rtcSetGeometryOccludedFunction(shapePtr, elxSphereOccludedFunc);
    rtcCommitGeometry(shapePtr);

    emitter = nullptr;
    emitter = nullptr;
    geomID  = RTC_INVALID_GEOMETRY_ID;
}

// todo
void elxSphere::sampleDirect(elxDirectSamplingRecord &dRec, const Point2f &sample) const {
    return;
}
// todo
void elxSphere::samplePosition(elxDirectSamplingRecord &dRec, const Point2f &sample) const {
    return;
}
// todo
float elxSphere::area() const {
    return .0f;
}

Vec3f elxSphere::getNormal(const elxRay &ray, const Point3f &hit, const Vec3f &nDir) const {
    // just return the hit - center
    return hit - center;
}

Point2f elxSphere::getUV(const Point3f &hit) const {
    //std::cout<<"Sphere has not implemented the getUV\n";
    return Point2f(.0f);
}

//todo
std::string elxSphere::toString() const {
    return "";
}


ELX_NAMESPACE_END