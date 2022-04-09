#include <eloimx/render/common.h>
#include <fmt/format.h>
ELX_NAMESPACE_BEGIN

elxDirectSamplingRecord::elxDirectSamplingRecord(const elxIntersection &its){
    ref = its.p;
    refN = its.geoFrame.toWorld(Vec3f(0, 1, 0));    
}


std::string elxDirectSamplingRecord::toString() const {
    return fmt::format("DirectSamplingRecord :\n refP=({}, {}, {})\n refN=({}, {}, {})\n direction=({}, {}, {})\n dist={}\n sampledP=({}, {}, {})\n Pnormal=({}, {}, {})\n pdf={})",
        ref.x, ref.y, ref.z,
        refN.x, refN.y, refN.z,
        d.x, d.y, d.z,
        dist,
        p.x, p.y, p.z,
        n.x, n.y, n.z,
        pdf);
}

ELX_NAMESPACE_END