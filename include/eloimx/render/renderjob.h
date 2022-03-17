#pragma once
#include <eloimx/eloimx.h>
#include <math.h>

ELX_NAMESPACE_BEGIN

class elxRenderJob {
    std::string imageName;
    char *color;

    elxRenderJob() { };
    float gamma(float x) const {
        if (x <= 0.0031308)
            return 12.92 * x;
        else {
            return 1.055 * std::pow(x, 0.4167) - 0.055;
        }
    }
public:
    unsigned height, width;
    unsigned spp;

    elxRenderJob(std::string imgName, unsigned height, unsigned width, unsigned spp):
        imageName(imgName), height(height), width(width), spp(spp){
        color = new char[height * width * 3];
    }

    ~elxRenderJob() {
        delete color;
    }

    inline void setPixel(unsigned x, unsigned y, const elxSpectrum &spc) {

        color[x * 3 + y * width * 3]     = (char) (std::sqrt(spc.r) * 255);
        color[x * 3 + y * width * 3 + 1] = (char) (std::sqrt(spc.g) * 255);
        color[x * 3 + y * width * 3 + 2] = (char) (std::sqrt(spc.b) * 255);
    }    

    void writeTga() const;
};

ELX_NAMESPACE_END