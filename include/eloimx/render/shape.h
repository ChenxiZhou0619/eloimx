#pragma once
#include <eloimx/eloimx.h>
#include <embree3/rtcore.h>
#include <fmt/format.h>

ELX_NAMESPACE_BEGIN
class elxBSDF;
class elxEmitter;
struct elxDirectSamplingRecord;
class Shape {
public:
    RTCGeometry shapePtr;

    void setBSDF(elxBSDF *bsdf) {
        this->bsdf = bsdf;
    }

    elxBSDF* getBSDF() const {
        return bsdf;
    }

    void boundEmitter(elxEmitter *emitter);

    elxEmitter* getEmitter() const {
        return emitter;
    }

    bool isEmitter() const {
        return this->emitter != nullptr;
    }

    void setGeomID(unsigned int geomID) {
        this->geomID = geomID;
    }

    unsigned int getGeomID() const {
        return this->geomID;
    }

    virtual void sampleDirect(elxDirectSamplingRecord &dRec, const Point2f &sample) const=0;

    virtual void samplePosition(elxDirectSamplingRecord &dRec, const Point2f &sample) const=0;

    virtual float area() const=0;

    virtual Vec3f getNormal(const elxRay &ray, const Point3f &hit, const Vec3f &nDir) const=0;

    virtual Point2f getUV(const Point3f &hit) const=0;
    
    virtual std::string toString() const=0;
protected:
    Shape() { }
    elxBSDF *bsdf;
    elxEmitter *emitter;
    unsigned int geomID;
};

class elxTriangle : public Shape {
public:
    elxTriangle(RTCDevice device,
                 const Point3f &p1,
                 const Point3f &p2,
                 const Point3f &p3);

    // sample a point on the surface             
    virtual void samplePosition(elxDirectSamplingRecord &dRec, const Point2f &sample) const;

    virtual void sampleDirect(elxDirectSamplingRecord &dRec, const Point2f &sample) const;

    virtual float area() const;

    virtual Vec3f getNormal(const elxRay &ray, const Point3f &hit, const Vec3f &nDir) const;

    virtual Point2f getUV(const Point3f &hit) const;

    virtual std::string toString() const;

protected:
    elxTriangle() { }
};

class elxRectangle : public Shape{
public:
    elxRectangle(RTCDevice device,
                 const Point3f &p1,
                 const Point3f &p2,
                 const Point3f &p3,
                 const Point3f &p4);

    virtual void samplePosition(elxDirectSamplingRecord &dRec, const Point2f &sample) const;

    virtual void sampleDirect(elxDirectSamplingRecord &dRec, const Point2f &sample) const;

    virtual float area() const;

    virtual Vec3f getNormal(const elxRay &ray, const Point3f &hit, const Vec3f &nDir) const;

    virtual Point2f getUV(const Point3f &hit) const;

    virtual std::string toString() const;

};

class elxSphere : public Shape{
    /*
    RTCGeometry geometry = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_USER);
    rtcSetGeometryUserPrimitiveCount(geometry, numPrimitives);
    rtcSetGeometryUserData(geometry, userGeometryRepresentation);
    rtcSetGeometryBoundsFunction(geometry, boundsFunction);
    rtcSetGeometryIntersectFunction(geometry, intersectFunction);
    rtcSetGeometryOccludedFunction(geometry, occludedFunction);
    */
public:
    Point3f center;
    float radius;

    elxSphere(RTCDevice device, const Point3f &c, const float &r);

    virtual void sampleDirect(elxDirectSamplingRecord &dRec, const Point2f &sample) const;

    virtual void samplePosition(elxDirectSamplingRecord &dRec, const Point2f &sample) const;

    virtual float area() const;

    virtual Vec3f getNormal(const elxRay &ray, const Point3f &hit, const Vec3f &nDir) const;

    virtual Point2f getUV(const Point3f &hit) const;

    virtual std::string toString() const;

protected:
    elxSphere() { }

};

ELX_NAMESPACE_END