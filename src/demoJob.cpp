#include <eloimx/eloimx.h>
#include <eloimx/render/integrator.h>
#include <eloimx/render/perspective.h>
#include <eloimx/integrators/path.h>
#include <eloimx/bsdfs/diffuse.h>
#include <eloimx/render/emitter.h>

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
    elxRenderJob job("cornellBox_100spp_10maxPath_sphere.tga", 400, 400, 100);
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

    /*--------------- sphere ---------------------*/
    elxSphere *sph = new elxSphere(
        device,
        Point3f(0, -0.5, 2),
        1.f
    );
    elxBSDF *gray = new elxDiffuse(elxSpectrum(.5f));
    sph->setBSDF(gray);
    scene->attachGeometry(sph);

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
    RTCDevice device = rtcNewDevice(nullptr);
    elxScene* scene = new elxScene(device);
    elxSphere sph(
        device,
        Point3f(0, 0, 0),
        1.0f
    );

    scene->attachGeometry(&sph);
    scene->commitScene();

    elxRay ray(Point3f(0, 0, -2), Vec3f(0, 0, 2));
    elxIntersection its;
    scene->rayIntersect(ray, its);
    std::cout<<its.toString()<<"\n";
#endif
}