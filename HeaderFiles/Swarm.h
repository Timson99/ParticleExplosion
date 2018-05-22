#ifndef SWARM_H_
#define SWARM_H_

#include <SDL.h>
#include "Particle.h"


namespace shortcuts {

    class Swarm {

    public:
        const static int NPARTICLES;

    private:
        Particle* m_pParticles;
        int lastUpdate;

    public:
        Swarm();
        ~Swarm();
        const Particle* const getParticles() const { return m_pParticles; }
        void update(int elapsed);

          



    };
}






#endif
