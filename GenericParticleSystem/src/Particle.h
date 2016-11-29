#pragma once

namespace vac {
template <typename VecType>
struct Particle {
    using vec_type = VecType;
    VecType prevPos;
    VecType pos;
    VecType vel;
    VecType acc;
    float mass = 1.0f;
};
}
