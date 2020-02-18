#ifndef TOOLSMARKER_H
#define TOOLSMARKER_H


#include <QColor>
#include "QGLViewer/qglviewer.h"
#include "DTrack.hpp"


/*!
 * \brief The ToolsMarker class. Elle fournie des outils pour la représentation des marqueurs ayant une position et une orientation.
 *
 *
 */
class ToolsMarker
{
public:
    static GLUquadric * quad;                //! Quadrique pour dessiner le marqueur

    static bool  axisDrawing;                //! Indicateur du style de représentation des marqueurs souhaité
    static int   nbMaxTraces;                //! Taille de l'historique des traces
    static int   sphereSize;                 //! Taille d'une sphère dans le cas d'une représentation par sphère
    static int   axisSize;                   //! Taille de l'axe dans le cas d'une représentation par axe

    static const int nbSlices    = 15;       //! Nombre de slices utilisé pour le dessin d'une sphère, de valeur 15
    static const int nbStacks    = 10;       //! Nombre de stacks utilisé pour le dessin d'une sphère, de valeur 10

    //! Dessin d'une sphère à la position pos, de taille size et de couleur color
    //! @param pos   - position du centre de la sphère
    //! @param color - couleur de la sphère
    //! @param size  - taille de la sphère
    static void drawSphere(const qglviewer::Vec &pos, const QColor &color , double size);

    //! Dessin d'un axe à la positon pos, d'orientation q, de taille size et de couleur color
    //! @param pos   - position du centre de l'axe
    //! @param q     _ quaternion encodant l'orientation de l'axe
    //! @param color - couleur de l'axe
    //! @param size  - taille de l'axe

    static void drawAxis  ( const qglviewer::Vec &pos, const qglviewer::Quaternion &q, const QColor & color, double size );

    //! Création d'un quatertion à partir d'une matrice de rotation ordonnée colonne
    //!@param rot : float * -> float[9] rotation matrix (column-wise)
    static qglviewer::Quaternion getQuaternion( const float * rot );
};




#endif // TOOLSMARKER_H
