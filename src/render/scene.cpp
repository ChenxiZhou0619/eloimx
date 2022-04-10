#include <eloimx/render/scene.h>
#include <eloimx/render/emitter.h>
ELX_NAMESPACE_BEGIN

elxSpectrum elxScene::sampleEmitterDirect(elxDirectSamplingRecord &dRec,
    const Point2f &sample, bool testVisibility) const {
    //return elxSpectrum(.0f);
    // one emitter in scene first
    if (emitters.size() == 0) {
        return elxSpectrum(.0f);
    }
    unsigned int index = 0;
    elxEmitter *emitter = emitters[index];
    elxSpectrum value = emitter->sampleDirect(dRec, sample);

    if (dRec.pdf != 0) {
        if (testVisibility) {
            elxRay ray(dRec.ref, dRec.d, Epsilon, dRec.dist - Epsilon);
            elxIntersection tempIts;
            this->rayIntersect(ray, tempIts);
            if (tempIts.isValid()) {
                // hit something else
                return elxSpectrum(.0f);    
            }
        }
        value /= dRec.pdf;
        return value;
    } else {
        return elxSpectrum(.0f);
    }
}

ELX_NAMESPACE_END
