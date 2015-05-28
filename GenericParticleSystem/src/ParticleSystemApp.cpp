#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#include "ParticleSystem.h"
#include "ParticleRenderer.h"
#include "Particle.h"
#include "PhysicsTool.h"
#include "IntegrationPolicy.h"

using ParticleSystemType = vac::ParticleSystem<std::vector<vac::Particle<ci::Vec2f> >, vac::EulerPolicy>;

class ParticleSystemApp : public AppNative {
public:
    void setup();
    void update();
    void draw();

private:
    ParticleSystemType m_pSystem;
    vac::ParticleRenderer m_renderer;
};

void ParticleSystemApp::setup()
{
    m_pSystem.initialize(500, [](ParticleSystemType::ParticleType& p) {
        p.pos = ci::Vec2d(0,0);
        auto randDir = Rand::randVec2f();
        auto velocity = Rand::randFloat(1);
        p.vel = velocity*randDir;
        p.mass = Rand::randFloat(10);

    });
}

void ParticleSystemApp::update()
{
    m_pSystem.applyForce([this](ParticleSystemType::ParticleType& particle) {
        auto force = ci::Vec2f(0,0.001);
        vac::physics::apply(particle, force);
        auto wind = ci::Vec2f(0.01,0.0);
        vac::physics::apply(particle, wind);
    });

    m_pSystem.update();
}

void ParticleSystemApp::draw()
{
    auto origin = getWindowCenter();
    gl::clear(Color::black());
    m_renderer.render(m_pSystem, [this, origin](const ParticleSystemType::ParticleType& p) {
        auto v = origin + p.pos;
        auto radius = p.mass;
        cinder::gl::drawSolidCircle(v, radius);
    });
}

CINDER_APP_NATIVE(ParticleSystemApp, RendererGl)
