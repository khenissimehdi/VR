#include "ARTMarker.h"
#include "ToolsMarker.h"

ARTMarker::ARTMarker(dtrack_marker_type marker)
{
    m_color = Qt::blue;
    id = marker.id;
    quality = marker.quality;
    m_position = qglviewer::Vec(marker.loc[0],marker.loc[1],marker.loc[2]);
    resizeTrace(ToolsMarker::nbMaxTraces);
}

void ARTMarker::addTrace(qglviewer::Vec position)
{
    if (m_posTraces.size() >= m_posTraces.capacity())
    {
        m_posTraces.removeFirst();
    }
    m_position = position;
    m_posTraces.push_back(position);

}

int ARTMarker::getId() {
    return id;
}

void ARTMarker::clearTrace()
{
    m_posTraces.clear();
}

void ARTMarker::resizeTrace(int size)
{
    m_posTraces.resize(size);
}

void ARTMarker::draw()
{

    int sizeSphere = 50;
    double alpha = 0.3;
    QColor color = m_color;

    for (int i = 0; i < m_posTraces.size(); i++)
    {
        sizeSphere += 1;
        alpha += 0.1;
        alpha = (alpha > 1.0) ? alpha = 1.0 : alpha;
        color.setAlphaF(alpha);
        ToolsMarker::drawSphere(m_posTraces.at(i), color, sizeSphere);
    }
}
