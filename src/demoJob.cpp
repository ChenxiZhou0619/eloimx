#include <eloimx/eloimx.h>
#include <eloimx/render/integrator.h>
#include <eloimx/render/perspective.h>
#include <eloimx/integrators/path.h>
#include <eloimx/bsdfs/diffuse.h>
#include <eloimx/render/emitter.h>
#include <eloimx/bsdfs/dielectric.h>
#include <eloimx/bsdfs/mirror.h>
#include <eloimx/bsdfs/conductor.h>
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
    elxRenderJob job("cornellBox_100spp_10maxPath_copper.tga", 400, 400, 100);
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
    elxBSDF *red = new elxDiffuse(elxSpectrum(1.0f, 0.5f, 0.5f));
    leftRec->setBSDF(red);
    scene->attachGeometry(leftRec);

    /*----------------- back --------------------------*/
    elxRectangle *backRec = new elxRectangle(
        device,
        Point3f(1.5, -1.5, 3),
        Point3f(-1.5, -1.5, 3),
        Point3f(-1.5, 1.5, 3),
        Point3f(1.5, 1.5, 3)
    );
    elxBSDF *green = new elxDiffuse(elxSpectrum(.5f, 1.0f, .5f));
    backRec->setBSDF(green);
    scene->attachGeometry(backRec);

    /*----------------- right --------------------------*/
    elxRectangle *rightRec = new elxRectangle(
        device,
        Point3f(-1.5, -1.5, 3),
        Point3f(-1.5, 1.5, 3),
        Point3f(-1.5, 1.5, 1),
        Point3f(-1.5, -1.5, 1)
    );
    elxBSDF *blue = new elxDiffuse(elxSpectrum(.5f, .5f, 1.f));
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
    elxBSDF *white = new elxDiffuse(elxSpectrum(1.f, 1.f, 1.f));
    downRec->setBSDF(white);
    scene->attachGeometry(downRec);

    /*--------------- up -------------------------*/
    elxRectangle *upRec = new elxRectangle(
        device,
        Point3f(1.5, 1.5, 1),
        Point3f(-1.5, 1.5, 1),
        Point3f(-1.5, 1.5, 3),
        Point3f(1.5, 1.5, 3)
    );
    elxBSDF *black = new elxDiffuse(elxSpectrum(.3f));
    upRec->setBSDF(black);
    scene->attachGeometry(upRec);

    /*--------------- sphere1 ---------------------*/
    elxSphere *sph1 = new elxSphere(
        device,
        Point3f(1.0f, -1.1, 2),
        .4f
    );
    elxBSDF *water1 = new elxDielectric(elxSpectrum(1.0f), elxSpectrum(1.0f), 1.33);
    sph1->setBSDF(water1);
    scene->attachGeometry(sph1);

    /*---------------- sphere2 --------------------*/
    elxSphere *sph2 = new elxSphere(
        device,
        Point3f(-0.5f, -0.5, 2),
        1.f
    );
    
    //elxBSDF *sphereRed = new elxDiffuse(elxSpectrum(0.7f, 0.4f, 0.4f));
    elxBSDF *copper = new elxConductor(elxSpectrum(1.f), "Copper");
    sph2->setBSDF(copper);
    scene->attachGeometry(sph2);

    /*--------------- sphere3 ---------------------*/
    elxSphere *sph3 = new elxSphere(
        device,
        Point3f(0.3f, -1.2, 1.25),
        .25f
    );
    elxBSDF *water2 = new elxDielectric(elxSpectrum(1.0f), elxSpectrum(1.0f), 1.5);
    sph3->setBSDF(water2);
    scene->attachGeometry(sph3);


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
#ifdef SINGLE_DEBUG
    elxRenderJob job("cornellBox_200spp_10maxPath_mirror.tga", 400, 400, 200);
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
    elxBSDF *mirror1 = new elxMirror(elxSpectrum(1.0f, 1.0f, 1.0f));
    leftRec->setBSDF(mirror1);
    scene->attachGeometry(leftRec);

    /*----------------- back --------------------------*/
    elxRectangle *backRec = new elxRectangle(
        device,
        Point3f(1.5, -1.5, 3),
        Point3f(-1.5, -1.5, 3),
        Point3f(-1.5, 1.5, 3),
        Point3f(1.5, 1.5, 3)
    );
    elxBSDF *green = new elxDiffuse(elxSpectrum(.5f, 1.0f, .5f));
    backRec->setBSDF(green);
    scene->attachGeometry(backRec);

    /*----------------- right --------------------------*/
    elxRectangle *rightRec = new elxRectangle(
        device,
        Point3f(-1.5, -1.5, 3),
        Point3f(-1.5, 1.5, 3),
        Point3f(-1.5, 1.5, 1),
        Point3f(-1.5, -1.5, 1)
    );
    elxBSDF *mirror2 = new elxMirror(elxSpectrum(1.f, 1.f, 1.f));
    rightRec->setBSDF(mirror2);
    scene->attachGeometry(rightRec);

    /*----------------- down --------------------------*/
    elxRectangle *downRec = new elxRectangle(
        device,
        Point3f(1.5, -1.5, 1),
        Point3f(1.5, -1.5, 3),
        Point3f(-1.5, -1.5, 3),
        Point3f(-1.5, -1.5, 1)
    );
    elxBSDF *white = new elxDiffuse(elxSpectrum(1.f, 1.f, 1.f));
    downRec->setBSDF(white);
    scene->attachGeometry(downRec);

    /*--------------- up -------------------------*/
    elxRectangle *upRec = new elxRectangle(
        device,
        Point3f(1.5, 1.5, 1),
        Point3f(-1.5, 1.5, 1),
        Point3f(-1.5, 1.5, 3),
        Point3f(1.5, 1.5, 3)
    );
    elxBSDF *black = new elxDiffuse(elxSpectrum(.3f));
    upRec->setBSDF(black);
    scene->attachGeometry(upRec);

    /*

    elxSphere *sph1 = new elxSphere(
        device,
        Point3f(1.0f, -1.1, 2),
        .4f
    );
    elxBSDF *water1 = new elxDielectric(elxSpectrum(1.0f), elxSpectrum(1.0f), 1.33);
    sph1->setBSDF(water1);
    scene->attachGeometry(sph1);

    elxSphere *sph2 = new elxSphere(
        device,
        Point3f(-0.5f, -0.5, 2),
        1.f
    );
    
    elxBSDF *sphereRed = new elxDiffuse(elxSpectrum(0.7f, 0.4f, 0.4f));
    sph2->setBSDF(sphereRed);
    scene->attachGeometry(sph2);

    elxSphere *sph3 = new elxSphere(
        device,
        Point3f(0.3f, -1.2, 1.25),
        .25f
    );
    elxBSDF *water2 = new elxDielectric(elxSpectrum(1.0f), elxSpectrum(1.0f), 1.5);
    sph3->setBSDF(water2);
    scene->attachGeometry(sph3);
    */

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