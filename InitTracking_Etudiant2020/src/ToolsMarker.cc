#include "ToolsMarker.h"

#include <QDebug>

bool ToolsMarker::axisDrawing   = false;
int  ToolsMarker::nbMaxTraces   = 10;
int  ToolsMarker::sphereSize    = 10;
int  ToolsMarker::axisSize      = 99;
GLUquadric * ToolsMarker::quad  = gluNewQuadric();



void ToolsMarker::drawSphere(const qglviewer::Vec &pos, const QColor & color, double size )
{
    glColor4f( color.redF(), color.greenF(), color.blueF(), color.alphaF() );
    glPushMatrix();
        glTranslatef( pos.x, pos.y, pos.z );
        gluSphere( quad, size,
                   ToolsMarker::nbSlices, ToolsMarker::nbStacks);
    glPopMatrix();

}

void ToolsMarker::drawAxis  (const qglviewer::Vec &pos, const qglviewer::Quaternion &q, const QColor & color , double size)
{
    glColor4f( color.redF(), color.greenF(), color.blueF(), color.alphaF() );
    glPushMatrix();
        glMultMatrixd( qglviewer::Frame( pos, q).matrix());
        QGLViewer::drawAxis( size );
    glPopMatrix();
}

qglviewer::Quaternion ToolsMarker::getQuaternion( const float * rot )
{
    qglviewer::Quaternion q;
    double matrix[3][3];
    int k,m,n;

    k=m=n=0;
    matrix[m][n] = rot[k++]; n++;
    matrix[m][n] = rot[k++]; n++;
    matrix[m][n] = rot[k++];
    n=0;m++;
    matrix[m][n] = rot[k++]; n++;
    matrix[m][n] = rot[k++]; n++;
    matrix[m][n] = rot[k++];
    n=0;m++;
    matrix[m][n] = rot[k++]; n++;
    matrix[m][n] = rot[k++]; n++;
    matrix[m][n] = rot[k++];
    n=0;m++;
    q.setFromRotationMatrix(matrix);

    return q;
}



