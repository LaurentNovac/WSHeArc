#pragma once

namespace vac {
namespace physics {
    template <typename ParticleType, typename ForceType>
    void applyForce(ParticleType& p, ForceType force)
    {
        force /= p.mass;
        p.acc += force;
    }
}
}
