#include <eloimx/render/sampler.h>
#include <random>
ELX_NAMESPACE_BEGIN

float elxSampler::sample1D() const {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(0, 1);
    return dis(gen);
}

Point2f elxSampler::sample2D() const {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(0, 1);
    return Point2f(dis(gen), dis(gen));
}

ELX_NAMESPACE_END