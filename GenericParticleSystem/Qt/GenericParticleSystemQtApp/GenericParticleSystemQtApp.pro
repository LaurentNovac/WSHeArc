#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T17:49:52
#
#-------------------------------------------------

QT       += core gui
CONFIG+=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GenericParticleSystemQtApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    ../../src/IntegrationPolicy.h \
    ../../src/Particle.h \
    ../../src/ParticleRenderer.h \
    ../../src/ParticleSystem.h \
    ../../src/PhysicsTool.h \
    ../../src/ParticleTraits.h

INCLUDEPATH+=../../src
FORMS    += mainwindow.ui
