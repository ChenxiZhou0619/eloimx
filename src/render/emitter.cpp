#include <eloimx/render/emitter.h>
#include <eloimx/render/common.h>
ELX_NAMESPACE_BEGIN
elxSpectrum elxAreaLight::eval(const elxIntersection &its, const Vec3f &d) const {
    // nothing to do but return the constant spectrum
    return m_emission;
}

elxSpectrum elxAreaLight::sampleDirect(elxDirectSamplingRecord &dRec, const Point2f &sample) const {
    m_shape->sampleDirect(dRec, sample);
    
    if (glm::dot(dRec.d, dRec.refN) >=0 && glm::dot(dRec.d, dRec.n) < 0 && dRec.pdf != 0) {
        return m_emission / dRec.pdf;
    } else {
        dRec.pdf = .0f;
        return elxSpectrum(.0f);
    }
}

std::string elxAreaLight::toString() const {
    return fmt::format("AreaLight emitter, {}, bounding to {}", m_emission.toString(), (void *)m_shape);
}
ELX_NAMESPACE_END