/*
    intersection.h
    create: 2022.2.25
*/
#pragma once
#include <eloimx/eloimx.h>
#include <eloimx/core/frame.h>
#include <eloimx/render/shape.h>
ELX_NAMESPACE_BEGIN
class elxBSDF;
struct elxIntersection {
    Shape *shape;
    
    float t;    // refer to the length of the ray

    Point3f p;  // intersection point in the 3D coordinates

    elxFrame geoFrame;

    elxFrame shFrame;

    Point2f uv; // uv coordinate of hit point on the surface

    //Vec3f dpdu, dpdv; // position partials

    float dudx, dudy, dvdx, dvdy;
    //float time;

    //Spectrum color; Interpolated vertex color

    Vec3f wi;   // incident direction in the local shading frame

    bool haveUVPartials;

    elxIntersection(){
        shape = nullptr;
        t = std::numeric_limits<float>::infinity();
        haveUVPartials = false;
        dudx = dudy = dvdx = dvdy = .0f;
    }

    inline bool isValid() const {
        return t != std::numeric_limits<float>::infinity();
    }
    
    elxBSDF* getBSDF(const elxRay &ray) const;

    inline bool isEmitter() const {
        return shape->getEmitter() != nullptr;
    }

    elxSpectrum Le(const Vec3f &d) const;

    Vec3f toLocal(const Vec3f &v) const;

    Vec3f toWorld(const Vec3f &v) const;

    std::string toString() const; 
};


ELX_NAMESPACE_END