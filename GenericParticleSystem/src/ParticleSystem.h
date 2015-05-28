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

template <typename ContainerType, typename IntegrationPolicy>
class ParticleSystem : public IntegrationPolicy {
public:
    using ParticleType = typename ContainerType::value_type;

    template <typename Fun>
    void initialize(size_t N, Fun initFun)
    {
        m_particles.resize(N);
        for (auto& p : m_particles) {
            initFun(p);
        }
    }

    void update()
    {
        for (auto& particle : m_particles) {
            IntegrationPolicy::integrate(particle);
        }
    }

    template <typename Fun>
    void applyForce(Fun forceFunc)
    {
        for (auto& particle : m_particles) {
            forceFunc(particle);
        }
    }

    typename ContainerType::iterator begin()
    {
        return std::begin(m_particles);
    }

    typename ContainerType::iterator end()
    {
        return std::end(m_particles);
    }

    typename ContainerType::const_iterator begin() const
    {
        return std::begin(m_particles);
    }

    typename ContainerType::const_iterator end() const
    {
        return std::end(m_particles);
    }

    typename ContainerType::size_type size()
    {
        return m_particles.size();
    }

private:
    ContainerType m_particles;
};
}