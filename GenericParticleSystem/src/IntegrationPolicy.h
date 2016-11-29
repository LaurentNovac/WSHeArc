#pragma once

#include "ParticleTraits.h"
//http://gafferongames.com/game-physics/integration-basics/
namespace vac {
struct EulerPolicy {
    template <typename ParticleType>
    static void integrate(ParticleType& p, double dt)
    {
        auto& pos = traits::access<ParticleType>::get_pos(p);
        auto& vel = traits::access<ParticleType>::get_vel(p);
        auto& acc = traits::access<ParticleType>::get_acc(p);

        pos += vel*dt;
        vel += acc * dt;
    }
};

struct VerletPolicy {
    template <typename ParticleType>
    static void integrate(ParticleType& p, double dt)
    {
        auto& pos = traits::access<ParticleType>::get_pos(p);
        auto& prevPos = traits::access<ParticleType>::get_prevPos(p);
        auto& acc = traits::access<ParticleType>::get_acc(p);

        pos = pos + (pos - prevPos) + acc * dt;
        prevPos = pos;
    }
};
}
