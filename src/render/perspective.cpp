
#include <eloimx/render/perspective.h>
#include <eloimx/render/sampler.h>
ELX_NAMESPACE_BEGIN

float elxPerspectiveCamera::generateRay(elxRay &ray, const Point2f &pixelUV, elxSampler *sampler) const {
    if (pixelUV.x > 1.0f || pixelUV.x < .0f ||
        pixelUV.y > 1.0f || pixelUV.y < .0f){
        std::cout << "Error in the pixelUV, fault range!\n";
        exit(-1);
    }
    
    Point3f topLeft(1.0f, 1.0f, .0f);
    Vec3f offset = Vec3f(film->resolution.x * pixelUV.x, film->resolution.y * pixelUV.y, .0f);
    Point3f pFilm = topLeft - offset;
    Vec3f rayDirection = pFilm - location;
    normalize(rayDirection);

    float tFilm = filmToCamera / rayDirection.z;
    Point3f rayOrigin = location + tFilm * rayDirection;
    ray = elxRay(rayOrigin, rayDirection);
    return 1.0f; 
}

ELX_NAMESPACE_END