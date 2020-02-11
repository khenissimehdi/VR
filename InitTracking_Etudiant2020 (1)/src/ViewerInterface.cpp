#include "ViewerInterface.h"
#include <QMessageBox>
#include <QSettings>

void ViewerInterface::changePortButtonText(const QString& t)
{
    portButton->setText(t);
}

ViewerInterface::ViewerInterface()
{
    setupUi(this);

    connect( viewer, SIGNAL(changePortButtonText(const QString&)), this, SLOT(changePortButtonText(const QString&)));
    connect( viewer, SIGNAL(changeReadUDP(bool)),                  this, SLOT(changeNameOfButtonPause(bool)) );
	
    connect( stereoButton,       SIGNAL(pressed(void)), viewer, SLOT(showStereoDialog()) );
    connect( portButton,         SIGNAL(pressed(void)), viewer, SLOT(changePort()) );

    connect( axisCheckBox,       SIGNAL(toggled(bool)),     viewer, SLOT(setAxisDrawing(bool)) );
    connect( axisSizeSpinBox,    SIGNAL(valueChanged(int)), viewer, SLOT(axisSizeChanged(int)) );


    ///  TODO - Connexion à compléter...






// ---------------  Ne pas modifier ce code
   viewer->show();
   viewer->pause( pauseButton->isChecked() );

}


ViewerInterface::~ViewerInterface()    {}


void ViewerInterface::closeEvent(QCloseEvent *event)
{
    Q_UNUSED( event )
    viewer->close();
}


void ViewerInterface::changeNameOfButtonPause( bool readActivated )
{
    if ( readActivated )
        pauseButton->setText("Lecture");
    else
        pauseButton->setText("Pause");
}


void ViewerInterface::about()
{
    QMessageBox::information(nullptr, tr("About BallTracking"),
                             tr("<Center><B>BallTracking</B>")+
                             tr("<BR>(coded in C++ with OpenGL and Qt)")+
                             tr("<BR>Author: Stéphanie Prévost, <B>CReSTIC SIC</B>")+
                             tr("<BR>stephanie.prevost@univ-reims.fr")+
                             tr("<BR>Université de Reims Champagne-Ardenne, France")
                             );
}

