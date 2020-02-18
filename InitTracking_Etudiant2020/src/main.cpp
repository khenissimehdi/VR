#include <qapplication.h>
#include <iostream>
#include "ViewerInterface.h"

int main(int argc, char** argv)
{
    QApplication application(argc,argv);

    QCoreApplication::setOrganizationName("IUT de Reims - Dpt-Info");
    QCoreApplication::setOrganizationDomain("CentreImage.univ-reims.fr");
    QCoreApplication::setApplicationName("initTracking");

    QGLFormat format;
    format.setStereo(true);
    QGLFormat::setDefaultFormat(format);

    ViewerInterface vi;
    vi.show();

    return application.exec();
}
