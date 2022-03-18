#pragma once
#include <eloimx/eloimx.h>

ELX_NAMESPACE_BEGIN
/*
    cosThetaI : Cosine of the angle between the normal and the incident ray
        (may be negative)
    cosThetaT : Argument used to return the cosine of the angle between the normal
        and the transmitted ray, will have the opposite sign of cosThetaI
    float eta : relative refractive index
*/
float fresnelDieletricExt(float cosThetaI, 
    float &cosThetaT, float eta);

struct elxSpectrum;

elxSpectrum fresnelConductorExact(float cosThetaI,
    const elxSpectrum &eta, const elxSpectrum &k);

ELX_NAMESPACE_END