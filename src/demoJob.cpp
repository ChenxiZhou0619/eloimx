#include <eloimx/eloimx.h>
#include <eloimx/render/integrator.h>
#include <eloimx/render/perspective.h>
#include <eloimx/integrators/path.h>
#include <eloimx/bsdfs/diffuse.h>
#include <eloimx/render/emitter.h>
#include <eloimx/bsdfs/dielectric.h>
#include <eloimx/bsdfs/mirror.h>
#include <eloimx/bsdfs/conductor.h>
#include <eloimx/texture/bitmap.h>
#include <eloimx/texture/constmap.h>
#define INTEGRATE_DEBUG
#ifndef INTEGRATE_DEBUG
#define SINGLE_DEBUG
#endif
void test() {
    using namespace eloimx;

    /*
    elxSampler *sampler = new elxSampler();
    for (int i = 0; i < 10; ++i) {
        std::cout<<sampler->sample1D()<<"\n";
    }
    */
#ifdef INTEGRATE_DEBUG
    elxRenderJob job("cornellBox_16spp_10maxPath_All_400x400.tga", 400, 400, 16);
    elxMCIntegrator *integrator = new elxPathTracer(10, 1, true, false);
    elxCameraInterface *sensor = new elxPerspectiveCamera();
    RTCDevice device = rtcNewDevice(nullptr);
    elxScene* scene = new elxScene(device);

    /*----------------- left -------------------------*/
    elxRectangle *leftRec = new elxRectangle(
        device,
        Point3f(1.5, -1.5, 1),
        Point3f(1.5, -1.5, 3),
        Point3f(1.5, 1.5, 3),
        Point3f(1.5, 1.5, 1)
    );
    elxBSDF *red = new elxDiffuse(new elxConstMap(elxSpectrum(1.0f, 0.5f, 0.5f)));
    leftRec->setBSDF(red);
    scene->attachGeometry(leftRec);

    /*----------------- back --------------------------*/
    elxRectangle *backRec = new elxRectangle(
        device,
        Point3f(1.5, 1.5, 3),
        Point3f(-1.5, 1.5, 3),
        Point3f(-1.5, -1.5, 3),
        Point3f(1.5, -1.5, 3)
    );
    //std::string filepath = "D:\\myEmbreeProject\\ayaka.jpg";
    //elxTexture *ayaka = new elxBitMap(filepath);
    elxBSDF *white = new elxDiffuse(new elxConstMap(elxSpectrum(1.0f, 1.0f, 1.0f)));
    backRec->setBSDF(white);
    scene->attachGeometry(backRec);
    
    /*----------------- right --------------------------*/
    elxRectangle *rightRec = new elxRectangle(
        device,
        Point3f(-1.5, -1.5, 3),
        Point3f(-1.5, 1.5, 3),
        Point3f(-1.5, 1.5, 1),
        Point3f(-1.5, -1.5, 1)
    );
    elxBSDF *blue = new elxDiffuse(new elxConstMap(elxSpectrum(.5f, .5f, 1.f)));
    rightRec->setBSDF(blue);
    scene->attachGeometry(rightRec);

    /*----------------- down --------------------------*/
    elxRectangle *downRec = new elxRectangle(
        device,
        Point3f(1.5, -1.5, 1),
        Point3f(1.5, -1.5, 3),
        Point3f(-1.5, -1.5, 3),
        Point3f(-1.5, -1.5, 1)
    );
    elxBSDF *green = new elxDiffuse(new elxConstMap(elxSpectrum(.5f, 1.0f, .5f)));
    downRec->setBSDF(green);
    scene->attachGeometry(downRec);

    /*--------------- up -------------------------*/
    elxRectangle *upRec = new elxRectangle(
        device,
        Point3f(1.5, 1.5, 1),
        Point3f(-1.5, 1.5, 1),
        Point3f(-1.5, 1.5, 3),
        Point3f(1.5, 1.5, 3)
    );
    elxBSDF *black = new elxDiffuse(new elxConstMap(elxSpectrum(.3f)));
    upRec->setBSDF(black);
    scene->attachGeometry(upRec);

    /*--------------- light source -------------------------*/
    elxRectangle *light = new elxRectangle(
        device,
        Point3f(.5f, 1.4, 2),
        Point3f(-.5f, 1.4, 2),
        Point3f(-.5f, 1.4, 1.5),
        Point3f(.5f, 1.4, 1.5)
    );
    elxEmitter *emitter = new elxAreaLight(elxSpectrum(1.f));
    light->boundEmitter(emitter);
    scene->attachGeometry(light);

    /*---------------- sphere1 -----------------------------*/
    elxSphere *sph1 = new elxSphere(
        device,
        Point3f(1.1, -1.3, 2),
        0.2
    );
    elxBSDF *copper = new elxConductor(
        new elxConstMap(elxSpectrum(1.f)),
        "Copper"
    );
    sph1->setBSDF(copper);
    scene->attachGeometry(sph1);

    /*------------------ sphere2 ---------------------------*/
    elxSphere *sph2 = new elxSphere(
        device,
        Point3f(-0.8, -1.1, 1.9),
        0.4
    );
    elxBSDF *water = new elxDielectric(
        new elxConstMap(elxSpectrum(1.f)),
        new elxConstMap(elxSpectrum(1.f)),
        1.33
    );
    sph2->setBSDF(water);
    scene->attachGeometry(sph2);

    /*--------------------- sphere3 -----------------------*/
    elxSphere *sph3 = new elxSphere(
        device,
        Point3f(0.3, -1.2, 1.5),
        0.3
    );
    elxBSDF *mirror = new elxMirror(
        new elxConstMap(elxSpectrum(1.f))
    );
    sph3->setBSDF(mirror);
    scene->attachGeometry(sph3);

    scene->commitScene();
    integrator->render(scene, &job, sensor);

#endif
#ifdef SINGLE_DEBUG
    elxRenderJob job("cornellBox_32spp_10maxPath_texture_test5.tga", 400, 400, 32);
    elxMCIntegrator *integrator = new elxPathTracer(10, 1, true, false);
    elxCameraInterface *sensor = new elxPerspectiveCamera();
    RTCDevice device = rtcNewDevice(nullptr);
    elxScene* scene = new elxScene(device);

    /*----------------- left -------------------------*/
    elxRectangle *leftRec = new elxRectangle(
        device,
        Point3f(1.5, -1.5, 1),
        Point3f(1.5, -1.5, 3),
        Point3f(1.5, 1.5, 3),
        Point3f(1.5, 1.5, 1)
    );
    elxBSDF *red = new elxDiffuse(new elxConstMap(elxSpectrum(1.0f, 0.5f, 0.5f)));
    leftRec->setBSDF(red);
    scene->attachGeometry(leftRec);

    /*----------------- back --------------------------*/
    elxRectangle *backRec = new elxRectangle(
        device,
        Point3f(1.5, 1.5, 3),
        Point3f(-1.5, 1.5, 3),
        Point3f(-1.5, -1.5, 3),
        Point3f(1.5, -1.5, 3)
    );
    std::string filepath = "D:\\myEmbreeProject\\ayaka.jpg";
    elxTexture *ayaka = new elxBitMap(filepath);
    elxBSDF *white = new elxDiffuse(ayaka);
    backRec->setBSDF(white);
    scene->attachGeometry(backRec);
    
    /*----------------- right --------------------------*/
    elxRectangle *rightRec = new elxRectangle(
        device,
        Point3f(-1.5, -1.5, 3),
        Point3f(-1.5, 1.5, 3),
        Point3f(-1.5, 1.5, 1),
        Point3f(-1.5, -1.5, 1)
    );
    elxBSDF *blue = new elxDiffuse(new elxConstMap(elxSpectrum(.5f, .5f, 1.f)));
    rightRec->setBSDF(blue);
    scene->attachGeometry(rightRec);

    /*----------------- down --------------------------*/
    elxRectangle *downRec = new elxRectangle(
        device,
        Point3f(1.5, -1.5, 1),
        Point3f(1.5, -1.5, 3),
        Point3f(-1.5, -1.5, 3),
        Point3f(-1.5, -1.5, 1)
    );
    elxBSDF *green = new elxDiffuse(new elxConstMap(elxSpectrum(.5f, 1.0f, .5f)));
    downRec->setBSDF(green);
    scene->attachGeometry(downRec);

    /*--------------- up -------------------------*/
    elxRectangle *upRec = new elxRectangle(
        device,
        Point3f(1.5, 1.5, 1),
        Point3f(-1.5, 1.5, 1),
        Point3f(-1.5, 1.5, 3),
        Point3f(1.5, 1.5, 3)
    );
    elxBSDF *black = new elxDiffuse(new elxConstMap(elxSpectrum(.3f)));
    upRec->setBSDF(black);
    scene->attachGeometry(upRec);

    /*--------------- light source -------------------------*/
    elxRectangle *light = new elxRectangle(
        device,
        Point3f(.5f, 1.4, 2),
        Point3f(-.5f, 1.4, 2),
        Point3f(-.5f, 1.4, 1.5),
        Point3f(.5f, 1.4, 1.5)
    );
    elxEmitter *emitter = new elxAreaLight(elxSpectrum(1.f));
    light->boundEmitter(emitter);
    scene->attachGeometry(light);

    scene->commitScene();
    integrator->render(scene, &job, sensor);

#endif
}