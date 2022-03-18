#include <eloimx/bsdfs/diffuse.h>

// {1} material

ELX_NAMESPACE_BEGIN
// todo
elxSpectrum elxDiffuse::sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const {
    std::cout<<"This should not be executed, Diffuse::sample function\n";
    if (elxFrame::cosTheta(bRec.wi) <= 0){
        return elxSpectrum(.0f);
    }
    //bRec.wo
    return m_diffuseReflectance->eval(*bRec.itsPtr, true);
}
// todo
elxSpectrum elxDiffuse::sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const {
    if (elxFrame::cosTheta(bRec.wi) <= 0)
        return elxSpectrum(.0f);
    
    bRec.wo = warp::squareToCosHemisphere(sample);
    bRec.eta = 1.0f;
    pdf = warp::squareToCosHemispherePdf(bRec.wo);
    return m_diffuseReflectance->eval(*bRec.itsPtr, true);
}
// todo
elxSpectrum elxDiffuse::eval(const elxBSDFSamplingRecord &bRec) const {
    if (elxFrame::cosTheta(bRec.wi) <= 0 ||
        elxFrame::cosTheta(bRec.wo) <= 0) {
        return elxSpectrum(.0f);
    }
    return m_diffuseReflectance->eval(*bRec.itsPtr, true) * (INV_PI * elxFrame::cosTheta(bRec.wo));
}
// todo
float elxDiffuse::pdf(const elxBSDFSamplingRecord &bRec) const {
    if (elxFrame::cosTheta(bRec.wi) <= 0 ||
        elxFrame::cosTheta(bRec.wo) <= 0) {
        return .0f;
    }
    return warp::squareToCosHemispherePdf(bRec.wo);
}

std::string elxDiffuse::toString() const {
    return fmt::format("Here is a diffuse, whose texture is {}",
        m_diffuseReflectance->toString());
}

ELX_NAMESPACE_END