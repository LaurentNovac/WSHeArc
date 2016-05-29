#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QPainter>
#include <QTimer>
#include <QVector2D>
#include <QDebug>

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
    timer = new QTimer(this);
    // setup signal and slot
    connect(timer, SIGNAL(timeout()),
          this, SLOT(queryUpdate()));
    timer->setInterval(0);
    timer->start();
    m_pSystem.initialize(500, [](ParticleSystemType::ParticleType& p) {
          p.pos = QVector2D(0,0);
        auto randDir = randVec2f();
        auto velocity = randFloat(1);
        p.vel = velocity*randDir;
        p.mass = randFloat(10);
    });
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPen blackPen(Qt::black);
    QBrush blackBrush(Qt::black);
    painter.setPen(blackPen);
    painter.setBrush(blackBrush);
    painter.setRenderHint(QPainter::Antialiasing);

    auto cWidget = ui->centralWidget;
    auto origin = QVector2D(cWidget->width()/2,cWidget->height()/2);
    m_renderer.render(m_pSystem, [this, origin,&painter](const ParticleSystemType::ParticleType& p) {
        auto v = origin + p.pos;
        auto radius = p.mass;
        painter.drawEllipse(v.x(),v.y(),radius, radius);
    });
}

void MainWindow::updateParticles(){
    m_pSystem.applyForce([this](ParticleSystemType::ParticleType& particle) {
        auto force = QVector2D(0,0.01);
        vac::physics::applyForce(particle, force);
        auto wind = QVector2D(0.01,0.0);
        vac::physics::applyForce(particle, wind);
    });

    m_pSystem.update();
}

void MainWindow::queryUpdate(){
    updateParticles();
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
