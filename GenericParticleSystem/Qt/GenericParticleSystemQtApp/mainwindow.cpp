#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QPainter>
#include <QTimer>
#include <QVector2D>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>

float randFloat(float low, float high){
    return low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));
}

float randFloat(float high){
    return randFloat(0.0f, high);
}

QVector2D randVec2f()
{
    float theta = randFloat( (float)M_PI * 2.0f );
    return QVector2D(cos( theta ), sin( theta ) );
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setSceneRect(-width()/2,-height()/2,width(),height());

    initEventLoop();
    initParticlesData();
}

void MainWindow::updateParticles(){
    m_pSystem.applyForce([this](ParticleSystemType::ParticleType& particle) {
        auto force = QVector2D(0,0.01);
        vac::physics::applyForce(particle, force);
        auto wind = QVector2D(0.0,0.0);
        vac::physics::applyForce(particle, wind);
    });

    m_pSystem.update();
    m_renderer.render(m_pSystem, [this](const ParticleSystemType::ParticleType& p, int i) {
        m_ellipses[i]->setPos(p.pos.x(),p.pos.y());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initEventLoop()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(updateParticles()));
    timer->setInterval(0);
    timer->start();
}

void MainWindow::initParticlesData()
{
    QBrush blackBrush(Qt::black);
    QBrush whiteBrush(Qt::blue);
    m_scene->setBackgroundBrush(whiteBrush);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(1);

    m_pSystem.initialize(PARTICLE_COUNT, [this, blackBrush,outlinePen](ParticleSystemType::ParticleType& p) {
        p.pos = QVector2D(0,0);

        auto randDir = randVec2f();
        auto velocity = randFloat(1);
        p.vel = velocity*randDir;
        p.mass = randFloat(10);
        m_ellipses.push_back(m_scene->addEllipse(p.pos.x(),p.pos.y(),p.mass,p.mass, outlinePen, blackBrush));
    });
}

