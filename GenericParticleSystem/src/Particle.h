#pragma once

namespace vac {
template <typename VecType>
struct Particle {
    VecType pos; // 8 bytes
    VecType vel; // 8 bytes
    VecType acc; // 8 bytes
    float mass = 1.0f; // 4 bytes
    float life = 0.0f; // 4 bytes
};
}