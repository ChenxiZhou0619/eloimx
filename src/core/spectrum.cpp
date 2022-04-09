#include <eloimx/core/spectrum.h>

ELX_NAMESPACE_BEGIN
std::string elxSpectrum::toString() const {
    return fmt::format("Spertrum is = [{}, {}, {}]",
        r, g, b);
} 
ELX_NAMESPACE_END