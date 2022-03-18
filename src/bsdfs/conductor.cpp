#include <eloimx/bsdfs/conductor.h>

ELX_NAMESPACE_BEGIN
/*
    red   : 630nm
    green : 532nm
    blue  : 465nm
*/
std::unordered_map<std::string, elxSpectrum> elxConductor::etaMap = {
    {"Copper", elxSpectrum(0.31357, 0.80757, 1.2657)}
};
std::unordered_map<std::string, elxSpectrum> elxConductor::kMap = {
    {"Copper", elxSpectrum(3.4059, 2.4886, 2.2880)}
};

elxConductor::elxConductor(elxTexture *reflectance, std::string metal) {
    std::unordered_map<std::string, elxSpectrum>::iterator it_eta = 
        etaMap.find(metal);
    std::unordered_map<std::string, elxSpectrum>::iterator it_k = 
        kMap.find(metal);
    if (it_eta == etaMap.end() || it_k == kMap.end()) {
        std::cout<<"Error type! Use the default type copper\n";
        m_eta = elxSpectrum(0.31357, 0.80757, 1.2657);
        m_k   = elxSpectrum(3.4059, 2.4886, 2.2880);
    } else {
        m_eta = it_eta->second;
        m_k   = it_k->second;
    }
    m_specularReflectance = reflectance;
}

Vec3f elxConductor::reflect(const Vec3f &wi) const {
    return Vec3f(-wi.x, wi.y, -wi.z);
}

// todo
elxSpectrum elxConductor::sample(elxBSDFSamplingRecord &bRec, const Point2f &sample) const {
    std::cout<<"This should not be executed, Conductor::sample function\n";
    if (elxFrame::cosTheta(bRec.wi) <= 0){
        return elxSpectrum(.0f);
    }
    //bRec.wo
    return elxSpectrum(.0f);
}

elxSpectrum elxConductor::sample(elxBSDFSamplingRecord &bRec, const Point2f &sample, float &pdf) const {
    if (elxFrame::cosTheta(bRec.wi) <= 0)
        return elxSpectrum(.0f);
    bRec.wo = reflect(bRec.wi);
    bRec.eta = 1.f;
    pdf = 1.f;

    return m_specularReflectance->eval(*bRec.itsPtr, true) * 
            fresnelConductorExact(elxFrame::cosTheta(bRec.wi), m_eta, m_k);
}

elxSpectrum elxConductor::eval(const elxBSDFSamplingRecord &bRec) const {
    if (elxFrame::cosTheta(bRec.wi) <= 0 ||
        elxFrame::cosTheta(bRec.wo) <= 0 ||
        std::abs(glm::dot(reflect(bRec.wi), bRec.wo)-1) > Epsilon)
        return elxSpectrum(.0f);
    return m_specularReflectance->eval(*bRec.itsPtr, true) *
            fresnelConductorExact(elxFrame::cosTheta(bRec.wi), m_eta, m_k);
}

float elxConductor::pdf(const elxBSDFSamplingRecord &bRec) const {
    if (elxFrame::cosTheta(bRec.wi) <= 0 ||
        elxFrame::cosTheta(bRec.wo) <= 0 ||
        std::abs(glm::dot(reflect(bRec.wi), bRec.wo)-1) > Epsilon)
        return .0f;
    return 1.f;
}

std::string elxConductor::toString() const {
    return fmt::format("Here is a conductor:\n eta=[{}, {}, {}]\n k=[{}, {}, {}]\n reflectance = {}",
        m_eta.r, m_eta.g, m_eta.b,
        m_k.r, m_k.g, m_k.b,
        m_specularReflectance->toString());
}

ELX_NAMESPACE_END