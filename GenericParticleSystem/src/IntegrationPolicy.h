#pragma once

namespace vac {
struct EulerPolicy {
    template <typename ParticleType>
    static void integrate(ParticleType& p)
    {
        p.vel += p.acc;
        p.pos += p.vel;

        p.acc *= 0;
    }
};
}
