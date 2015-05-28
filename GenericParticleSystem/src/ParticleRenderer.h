#pragma once

#include "ParticleSystem.h"

namespace vac {

class ParticleRenderer {
public:
    template <typename RenderFun, typename ParticleSystemType>
    void render(const ParticleSystemType& pSystem, RenderFun rFun)
    {
        for (const auto& p : pSystem) {
            rFun(p);
        }
    }
};
}
