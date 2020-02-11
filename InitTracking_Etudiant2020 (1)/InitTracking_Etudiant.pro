####  Init tracking - 
####        Affichage des différents éléments que peut suivre le système ART 
####        de la salle d'Immersion du Centre Image
####  Squelette de l'application à destination des étudiants


TEMPLATE = app

TARGET  = initTracking
DESTDIR = $$PWD

DEPENDPATH        += .
win32:OBJECTS_DIR  = obj
unix:OBJECTS_DIR   = obj
MOC_DIR            = moc
UI_DIR             = obj

CONFIG *= with_QGLViewer


INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/ui

# --- sources
  # --- perso
    HEADERS = src/ViewerInterface.h \
              src/StereoDialog.h \
              src/Viewer.h

    SOURCES = src/main.cpp \
              src/ViewerInterface.cpp \
              src/Viewer.cpp

    SOURCES += src/ToolsMarker.cc
    HEADERS += src/ToolsMarker.h

  # --- DTrack (fournit par ART)
    SOURCES += src/DTrack.cpp
    HEADERS += src/DTrack.hpp


# --- Interfaces
    FORMS *= src/ui/viewerInterface.Qt4.ui \
             src/ui/stereo.ui


# ---- Config Qt
# ------------------------
QT     += core gui widgets
QT     += opengl xml
CONFIG += opengl xml
CONFIG += console


# --- Ajout des Lib
# -----------------------

  # --- QGLViewer
    with_QGLViewer {
        message( inclusion - QGLViewer )
        win32-g++ {
            CONFIG *=  qt opengl
            QT *= opengl xml
            QT *= gui    widgets

            QGLViewerDIR  = $$[QT_INSTALL_PLUGINS]/libQGLViewer-2.6.4/
            INCLUDEPATH  += $${QGLViewerDIR}
            DEFINES *= WIN32
CONFIG(debug, debug|release) {
 message( inclusion - QGLViewer mode debug )
            LIBS   += -L$${QGLViewerDIR}/QGLViewer -lQGLViewerd2
} else{
 message( inclusion - QGLViewer mode release )
            LIBS += -L$${QGLViewerDIR}/QGLViewer -lQGLViewer2
}

            LIBS += -lopengl32 -lglu32
        }
    }


  # --- Gestion des sockets
    win32:LIBS += -lwsock32


