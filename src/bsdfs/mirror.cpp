#include <eloimx/bsdfs/mirror.h>

ELX_NAMESPACE_BEGIN

Vec3f elxMirror::reflect(const Vec3f &wi) const {
    return Vec3f(-wi.x, wi.y, -wi.z);
}

elxSpectrum elxMirror::sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const {
    std::cout<<"This should not be executed, Glass::sample function\n";
    if (elxFrame::cosTheta(bRec.wi) <= 0){
        return elxSpectrum(.0f);
    }
    //bRec.wo
    return elxSpectrum(.0f);
}

elxSpectrum elxMirror::sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const {
    bRec.wo = reflect(bRec.wi);
    bRec.eta = 1.0f;
    pdf = 1.f;
    return m_specularReflectance;
}

elxSpectrum elxMirror::eval(const elxBSDFSamplingRecord &bRec) const {
    return m_specularReflectance;
}

float elxMirror::pdf(const elxBSDFSamplingRecord &bRec) const {
    return 1.0f;
}

std::string elxMirror::toString() const {
    return fmt::format("Here is a mirror:\n specularReflectance[{}, {}, {}]",
        m_specularReflectance.r, m_specularReflectance.g, m_specularReflectance.b);
}

ELX_NAMESPACE_END