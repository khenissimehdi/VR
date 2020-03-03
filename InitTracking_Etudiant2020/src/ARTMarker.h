#ifndef ARTMARKER_H
#define ARTMARKER_H


#include <QColor>
#include <QGLViewer/qglviewer.h>
#include <QVector>
#include "DTrack.hpp"
using namespace std;

class ARTMarker
{
public:
    ARTMarker(dtrack_marker_type);
    void addTrace();
    void clearTrace();
    void resizeTrace(int size);
    void draw();
protected:
    int id;               // id number (starting with 0)
    float quality;        // quality (0 <= qu <= 1, no tracking if -1)
    QColor m_color;
    qglviewer::Vec m_position; // Position actuelle
    QVector<qglviewer::Vec> m_posTraces; // Historique (position)
};

#endif // ARTMARKER_H
