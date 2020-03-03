#include "ARTMarker.h"
#include "ToolsMarker.h"

ARTMarker::ARTMarker(dtrack_marker_type marker)
{
    m_color = Qt::blue;
    id = marker.id;
    quality = marker.quality;
    m_position = qglviewer::Vec(marker.loc[0],marker.loc[1],marker.loc[2]);
    resizeTrace(ToolsMarker::nbMaxTraces);
    addTrace();
}

void ARTMarker::addTrace()
{
    if (m_posTraces.size() >= m_posTraces.capacity())
    {
        m_posTraces.removeFirst();
    }
    m_posTraces.push_back(m_position);

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
    ToolsMarker::drawSphere(m_position, m_color, 200);
}
