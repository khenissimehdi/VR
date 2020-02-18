#ifndef __STEREO_DIALOG_H__
#define __STEREO_DIALOG_H__

#include <ui_stereo.h>


class StereoDialog : public QDialog, public Ui::StereoDialog
{
public:
    StereoDialog()
    {
        setupUi(this);
    }
};


#endif


