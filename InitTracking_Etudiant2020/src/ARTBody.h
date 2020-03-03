#ifndef ARTBODY_H
#define ARTBODY_H

#include "ARTMarker.h"

class ARTBody :
{
public:
    ARTBody();
private:
protected:
    qglviewer::Quaternion m_q; // Position et orientation actuelle
    qglviewer::Quaternion m_qTraces; // Historique (position et orientation)
};

#endif // ARTBODY_H
