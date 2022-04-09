#include <eloimx/core/util.h>

ELX_NAMESPACE_BEGIN

/*
    the Fresnel reflectance is the average of the squares of the
        parallel and perpendicular polarization terms
*/
float fresnelDieletricExt(float cosThetaI_, 
    float &cosThetaT_, float eta) {
    
    if (eta == 1) {
        // no refraction
        cosThetaT_ = - cosThetaI_;
        return .0f;
    }

    /* Using Snell law */
    float scale = (cosThetaI_ > 0) ? 1/eta : eta,
          cosThetaT2 = 1 - (1 - cosThetaI_ * cosThetaI_) * (scale * scale);

    if (cosThetaT2 <= .0f) {
        // total internal reflection
        cosThetaT_ = .0f;
        return 1.f;
    }

    /* Find the absolute cosines of the incident/transmitted rays */
    float cosThetaI = std::abs(cosThetaI_);
    float cosThetaT = std::sqrt(cosThetaT2);

    float rPrl = (eta * cosThetaI - cosThetaT) / (eta * cosThetaI + cosThetaT);
    float rPpd = (cosThetaI - eta * cosThetaT) / (cosThetaI + eta * cosThetaT);
    
    cosThetaT_ = (cosThetaI_ > 0) ? -cosThetaT : cosThetaT;

    return .5f * (rPrl * rPrl + rPpd * rPpd);
}

elxSpectrum fresnelConductorExact(float cosThetaI,
    const elxSpectrum &eta, const elxSpectrum &k) {
    
    float cosThetaI2 = cosThetaI * cosThetaI,
          sinThetaI2 = 1 - cosThetaI2,
          sinThetaI4 = sinThetaI2 * sinThetaI2;

    elxSpectrum temp1 = eta*eta - k*k - elxSpectrum(sinThetaI2),
                a2pb2 = (temp1*temp1 + k*k*eta*eta*4).safe_sqrt(),
                a     = ((a2pb2 + temp1) * 0.5f).safe_sqrt();
    elxSpectrum term1 = a2pb2 + elxSpectrum(cosThetaI2),
                term2 = a * (2 * cosThetaI);
    elxSpectrum rPpd = (term1 - term2) / (term1 + term2);

    elxSpectrum term3 = a2pb2*cosThetaI2 + elxSpectrum(sinThetaI4),
                term4 = term2 * sinThetaI2;
    elxSpectrum rPrl = rPpd * (term3 - term4)/(term3 + term4);

    return (rPrl + rPpd) * 0.5f;
}

ELX_NAMESPACE_END