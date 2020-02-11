#ifndef VIEWERINTERFACE_H
#define VIEWERINTERFACE_H

#include <ui_viewerInterface.Qt4.h>

/*!
 * \brief The ViewerInterface class, Classe représentatant l'interface de l'application (viewer+ widgets de controle)
 */
class ViewerInterface : public QDialog, public Ui::Dialog
{
     Q_OBJECT

public slots:
    void changePortButtonText(const QString&);
    void about();
    void changeNameOfButtonPause(bool readActivated );

public:
    ViewerInterface();
   ~ViewerInterface();

private:
    void closeEvent(QCloseEvent *event);
    void setSettingsViewer();

};

#endif // VIEWERINTERFACE_H
