#ifndef ARTFLYSTICK_H
#define ARTFLYSTICK_H

#include "ARTBody.h"

class ARTFlystick : public ARTBody
{
public:
    ARTFlystick();
private:
protected:
    qglviewer::Quaternion m_q;
    qglviewer::Quaternion m_qTraces;;
};

#endif // ARTFLYSTICK_H
