#include <QApplication>
#include <iostream>

#include "FrameWidget.h"
#include "MainWindow.h"
#include "OpenCVCamera.h"
#include "DummyProcessor.h"
#include "RefPtr.h"
#include "Pipeline.h"
#include "CameraProducer.h"
#include "InspectorFactory.h"

using namespace plv;
using namespace plvgui;

int main(int argc, char **argv)
{
    //plv::OpenCVCamera* camera = new plv::OpenCVCamera( 0 );
    //assert(camera);
    //if( camera->init() != 0 )
     //   return -1;

    //camera->setDimensions( 640, 480 );

    QApplication app(argc, argv);

    InspectorFactory::create(typeid(OpenCVImage).name());
//    plvgui::CameraWindow* mainWin = new plvgui::CameraWindow(camera);
    MainWindow* mainWin = new MainWindow();
    FrameWidget* cvWidget = new FrameWidget( mainWin );

    // Make a pipeline
    RefPtr<Pipeline> pipeline = new Pipeline();
    // Make a CameraProducer
    RefPtr<CameraProducer> cp = new CameraProducer();
    // Add it to the pipeline
    pipeline->add(cp);

    // Make a DummyProcessor
//    RefPtr<DummyProcessor> dp = new DummyProcessor();
    // Add it to the pipeline as well
//    pipeline->add(dp);

//    cp->getOutputPin("output")->????

    cp->produce();

    //cvWidget->setSource(camera);

    //mainWin->addCamera(camera);
    //mainWin->addWidget( cvWidget );

    mainWin->setPipeline(pipeline);

    mainWin->show();

    //camera->start();

    int retval = app.exec();

    // Terminate camera thread
    //camera->release();
    //camera->exit();

    return retval;
}

