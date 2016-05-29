#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QVector2D>
#include "ParticleSystem.h"
#include "ParticleRenderer.h"
#include "Particle.h"
#include "PhysicsTool.h"
#include "IntegrationPolicy.h"
#include "ParticleTraits.h"
#include <QMainWindow>


using ParticleType = vac::Particle<QVector2D>;
using ParticleSystemType = vac::ParticleSystem<std::vector<ParticleType>, vac::EulerPolicy>;

namespace vac{
namespace traits{
    template<> struct access<ParticleType>{
        static QVector2D& get_pos(ParticleType& p)
        {
            return p.pos;
        }
        static QVector2D& get_vel(ParticleType& p)
        {
            return p.vel;
        }
        static QVector2D& get_acc(ParticleType& p)
        {
            return p.acc;
        }
    };
}
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    ParticleSystemType m_pSystem;
    vac::ParticleRenderer m_renderer;
    QTimer *timer;
    void updateParticles();

public slots:
    void queryUpdate();
};

#endif // MAINWINDOW_H
