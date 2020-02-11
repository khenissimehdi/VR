#include "Viewer.h"

#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

#include <iostream>


#define DEFAULTREADINGPORT 5000


Viewer::Viewer(QWidget *parent) : QGLViewer(parent),
    m_stereoDialog(nullptr), m_port(DEFAULTREADINGPORT)
{
    // Creation du Tracker de ART
    doBindTracker();

    // Creation et setting de la fenetre de paramétrage de la stereo
    setStereoDialog();

    setTrackingConnect();
}


Viewer::~Viewer()
{}


void Viewer::showEvent( QShowEvent * event )
{
    Q_UNUSED(event)
    emit changePortButtonText(QString("Change port (%1)").arg(m_port));
}

//// TODO - A compléter avec les instructions à executer dans le cas
////        de la fermeture de l'instance
void Viewer::closeEvent(QCloseEvent *event)
{
    Q_UNUSED( event )

    saveStateToFile();
    gluDeleteQuadric( ToolsMarker::quad );

    //// TODO - Ménage

}


//// TODO - Instanciation du tracker de ART avec vérification
////         qu'aucune erreur n'ai eu lieu.
int Viewer::doBindTracker()
{


    return 1;
}



//// TODO - initialisation de l'interval du Timer
////        et connection à la méthode à exécuter lors de son déclenchement
void Viewer::setTrackingConnect()
{
}


//// TODO - Lecture des données émises par le système de tracking
void Viewer::readARTData()
{
}



void Viewer::setStereoDialog()
{
// Creation de la fenetre de paramétrage de la stereo
    m_stereoDialog = new StereoDialog();
    if ( !m_stereoDialog )
    {
        qDebug() << "setStereoDialog() : Problème de mémoire";
        qApp->exit(-1);
    }
    m_stereoDialog->setWindowFlags(Qt::Tool);

// Init des valeurs des controles
    QSettings settings;
    double tmp;

    tmp=settings.value("focaldist",2000).toDouble();
    camera()->setFocusDistance(tmp);
    m_stereoDialog->sbFocal->setValue(tmp);

    tmp=settings.value("iodistance",4.5).toDouble();
    std::cerr << " iodistance tmp = " << tmp <<  std::endl;
    camera()->setIODistance(tmp*0.01);
    m_stereoDialog->sbIODistance->setValue(tmp);

    tmp=settings.value("physdisttoscreen",2.).toDouble();
    camera()->setPhysicalDistanceToScreen(tmp);
    m_stereoDialog->sbScreenDistance->setValue(tmp);

    tmp=settings.value("physscreenwidth",3.7).toDouble();
    camera()->setPhysicalScreenWidth(tmp);
    m_stereoDialog->sbScreenWidth->setValue(tmp);

    m_stereoDialog->cbStereo->setChecked( true );


// connecting the elements
    connect(m_stereoDialog->cbStereo,         SIGNAL(stateChanged(int)),    this, SLOT(changeStereo(int)));
    connect(m_stereoDialog->sbFocal,          SIGNAL(valueChanged(double)), this, SLOT(setFocusDistance(double)));
    connect(m_stereoDialog->sbIODistance,     SIGNAL(valueChanged(double)), this, SLOT(setIODistance(double)));
    connect(m_stereoDialog->sbScreenDistance, SIGNAL(valueChanged(double)), this, SLOT(setPhysicalDistanceToScreen(double)));
    connect(m_stereoDialog->sbScreenWidth,    SIGNAL(valueChanged(double)), this, SLOT(setPhysicalScreenWidth(double)));

    updateGL();

}




/// ------------------ SLOTs   avec l'interface
///
void Viewer::changeStereo( int val )
{
    setStereoDisplay( val==Qt::Checked );
}


//// NOPE - TODO - Arrêt de la lecture des marqueurs
void Viewer::pause( bool val )
{
    if ( val )  m_trackingTimer.stop();
    else
    {
        m_trackingTimer.start();
    }

    emit( changeReadUDP(val) );
}


//// TODO - Oubli de tous les marqueurs détectés et suivis par l'application
void Viewer::clear()
{
}


void Viewer::about()
{
    QMessageBox::information(this, tr("About initTracking"),
                             tr("<Center><B>init Tracking</B>")+
                             tr("<BR>(coded in C++ with OpenGL and Qt)")+
                             tr("<BR>Author: , <B>CReSTIC SIC</B>")+
                             tr("<BR>Email: ")+
                             tr("<BR>IUT de Reims, France")
                             );
}


void Viewer::changePort()
{
    bool ok;
    int d = QInputDialog::getInt(this, tr("Change the port"),tr("New port :"), m_port, 0, 65535, 1, &ok);

    if (ok)
    {
        m_port = d;
        if ( doBindTracker() )
        {
            emit changePortButtonText(QString("Change port (%1)").arg(m_port));
        }
    }
}

/// TODO - Méthodes SLOTs pour interagir avec les widgets de l'interface
void Viewer::intervalChanged( int val )
{
    Q_UNUSED(val)
}

void Viewer::traceLimitChanged( int val )
{
    Q_UNUSED(val)

/// ------ Ne pas modifier le code qui suit
    updateGL();
}

void Viewer::sphereSizeChanged( int val )
{
    Q_UNUSED(val)
}






void Viewer::showStereoDialog()
{
    m_stereoDialog->show();
}





///   liens avec stereoDialog
///
void Viewer::setFocusDistance(double d)
{
    camera()->setFocusDistance( d );
}

void Viewer::setIODistance(double d)
{
    camera()->setIODistance( d*0.01 );
}

void Viewer::setPhysicalDistanceToScreen(double d)
{
    camera()->setPhysicalDistanceToScreen( d );
}

void Viewer::setPhysicalScreenWidth(double d)
{
    camera()->setPhysicalScreenWidth( d );
}
void Viewer::setAxisDrawing( bool val )
{
    ToolsMarker::axisDrawing  = val; updateGL();
}
void Viewer::axisSizeChanged( int val )
{
    ToolsMarker::axisSize = val; updateGL();
}




/// __________________ Q G L V i e w e r  _____________
///
void Viewer::init() {
  // Restore previous viewer state.
     restoreStateFromFile();

  // Define the scene
     qglviewer::Vec m(-1, -1, -1),M(1, 1, 1);
     m*=1000;
     M*=1000;
     setSceneBoundingBox(m,M);
     showEntireScene();
     setStereoDisplay( true   );

     glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
     glEnable( GL_DEPTH_TEST );

  // Opens help window
     help();

  // Start animation loop
     startAnimation();
}



//// TODO - écriture des informations textes
void Viewer::drawInfo       ()
{
}



//// TODO - Dessins des marqueurs détectés
void Viewer::drawMarkers    ()
{
}

// Ne pas modifier cette méthode
void Viewer::draw()
{
    glColor3f(1.,1.,0.);
// ----- Affichage des écritures
    drawInfo();

// ----- Dessins des marqueurs
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);

    drawMarkers();

    glDisable(GL_BLEND);
}


QString Viewer::helpString() const
{
    QString txt("<h2>I n i t T r a c k i n g</h2>");

    return txt;
}
