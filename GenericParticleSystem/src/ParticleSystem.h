#pragma once

namespace vac {

template <typename ContainerTypeT, typename IntegrationPolicy>
class ParticleSystem : public IntegrationPolicy {
public:
    using ContainerType = ContainerTypeT;
    using ParticleType = typename ContainerType::value_type;

    template <typename Fun>
    void initialize(size_t N, Fun initFun)
    {
        m_particles.resize(N);
        for (auto& p : m_particles) {
            initFun(p);
        }
    }

    void update(double dt)
    {
        for (auto& particle : m_particles) {
            IntegrationPolicy::integrate(particle,dt);
        }
    }

    template <typename Fun>
    void applyForce(Fun forceFunc)
    {
        int i = 0;
        for (auto& particle : m_particles) {
            forceFunc(particle, i++);
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
