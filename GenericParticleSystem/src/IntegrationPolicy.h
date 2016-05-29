#pragma once

#include "ParticleTraits.h"

namespace vac {
struct EulerPolicy {
    template <typename ParticleType>
    static void integrate(ParticleType& p)
    {
        auto& pos = traits::access<ParticleType>::get_pos(p);
        auto& vel = traits::access<ParticleType>::get_vel(p);
        auto& acc = traits::access<ParticleType>::get_acc(p);

        vel += acc;
        pos += vel;

        acc *= 0;
    }
};
}
