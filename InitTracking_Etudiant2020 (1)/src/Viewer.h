#ifndef VIEWER_H__INIT_TRACKER
#define VIEWER_H__INIT_TRACKER


#include <QGLViewer/qglviewer.h>
#include "DTrack.hpp"

#include <StereoDialog.h>

#include <QTimer>
#include <QMap>

#include "ToolsMarker.h"

/*!
 * \brief The Viewer class, classe permettant une visualisation avec OpenGL
 *        Dérive de QGLViewer
 *        Ce widget visualise les données issues d'un système ART, récupérées sur le port UDP par une instance de DTrack.
 */
class Viewer : public QGLViewer
{
    Q_OBJECT

public :
            Viewer(QWidget *parent);
    virtual ~Viewer() override;


signals:
    void changePortButtonText(const QString &);
    void changeReadUDP( bool readActivated );

public slots:
 /// Liens avec l'interface du viewer
    void pause     ( bool val );                    //! pause sur la lecture des données ART
    void clear();                                   //! Vide l'historisque et les marqueurs déjà connues et réinitialise la connection UDP
    void about();                                   //! Information concernant l'application et le développeur
    void changePort();                              //! Demande le port UDP à utiliser à l'utilisateur et initialise la connection UDP
    void showStereoDialog();                        //! Affiche ou cache la fenetre de paramétrage stereo

    void intervalChanged( int val );                //! Change l'interval entre 2 lectures sur le port UDP effectué par le tracker.
    void traceLimitChanged( int val );              //! Définit la taille de l'historique pour tous les marqueurs
    void setAxisDrawing( bool val );                //! Fixe suivant la valeur de val si les marqeurs seront représentés par un axe
    void axisSizeChanged( int val );                //! Définit la taille de l'axe utilisé pour représenter un marqueur
    void sphereSizeChanged( int val );              //! Définit la taille de la sphère utilisée pour représenter un marqueur

 /// Liens avec l'interface stéréo
    void changeStereo               ( int val  );     //! (Des)Active la stéréo quadbuffer
    void setFocusDistance           ( double d );     //! Définit la distance focale
    void setIODistance              ( double d );     //! Définit la distance interoculaire
    void setPhysicalDistanceToScreen( double d );     //! Définit la distante à l'écran physique
    void setPhysicalScreenWidth     ( double d );     //! Définit la largeur de l'écran physique


 /// Méthodes à implémenter
    void readARTData    ();                         //! Effectue la lecture sur le port UDP des données ART et les traite
    void drawMarkers    ();                         //! Dessine les marqueurs détectés avec leur traces
    void drawInfo       ();                         //! Dessine en texte les informations concernant le tracking

protected :

    virtual void    draw      () Q_DECL_OVERRIDE;           //! Méthode générale pour le dessin de la scène OpenGL + info 2D
    virtual void    init      () Q_DECL_OVERRIDE;           //! Initialisation de la scène OpenGL
    virtual QString helpString() const Q_DECL_OVERRIDE;     //! Information explicative sur l'application


    void setStereoDialog    ();                     //! Initialise les paramètres stéréo pour la salle du CI
    int  doBindTracker      ();                     //! Initialise le tracker DTrack avec la connexion UDP
    void setTrackingConnect ();                     //! Mise en place de la boucle de tracking


    void showEvent      ( QShowEvent  *event ) override;
    void closeEvent     ( QCloseEvent *event ) override;



private :
    // Attributs pour la stereo
       StereoDialog * m_stereoDialog;

    // Attributs pour le tracking
       int            m_port;
       QTimer         m_trackingTimer;  // timer de déclenchement de la lecture des données sur UDP

 //// TODO - autres Attributs pour le tracking

};





#endif
