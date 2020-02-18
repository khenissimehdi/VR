#ifndef ARTMARKER_H
#define ARTMARKER_H


#include <QColor>
#include <QGLViewer/qglviewer.h>


class ARTMarker
{
public:
    ARTMarker();
private:
    int id;               // id number (starting with 0)
    float quality;        // quality (0 <= qu <= 1, no tracking if -1)
protected:
    QColor m_color;
    qglviewer::Vec m_position;
    qglviewer::Vec m_posTraces;
};

#endif // ARTMARKER_H
