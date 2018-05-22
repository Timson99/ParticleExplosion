#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <SDL.h>
#include <cstdlib>

namespace shortcuts {

    struct Particle {

        double m_x;
        double m_y;
        //double xspeed;
        //double yspeed;

    private:
        double m_speed;
        double m_direction;

    private:
        void init();

    public:
        Particle();
        void update(int interval);


    };
}






#endif 