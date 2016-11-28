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
}
