/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  File name     :  Particle.cpp
*  Purpose       :  Create a Particle Fire Simulation in SDL
*  @author       :  T. Herrmann
*  Date written  :  2018-05-20
*  Description   :  Particle Source File
*  Notes         :  None
*  Warnings      :  None
*  Exceptions    :  None
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Revision History
*  ---------------
*            Rev      Date     Modified by:  Reason for change/modification
*           -----  ----------  ------------  -----------------------------------------------------------
*  @version 1.0.0  2018-??-???? T. Herrmann  Initial writing and release
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <iostream>
#include <cmath>
#include "Particle.h"
using namespace std;

namespace shortcuts {

    Particle::Particle(): m_x(0), m_y(0) {
        //m_x = ((2.0 * rand()) / RAND_MAX) - 1; //Random Num [-1,1]
        //m_y = ((2.0 * rand()) / RAND_MAX) - 1; //Random Num [-1,1]
        //xspeed = 0.002 * (((rand() * 2.0) / RAND_MAX) - 1.0);
        //yspeed = 0.002 * (((rand() * 2.0) / RAND_MAX) - 1.0);

        init();
    }

    void Particle::init() {
        m_x = 0;
        m_y = 0;
        m_direction = ((rand() * 2.0 * M_PI) / RAND_MAX);
        m_speed = ((rand() * 0.4) / RAND_MAX);
        m_speed *= (m_speed);
    }

    void Particle::update(int interval) {
        
        double xspeed = m_speed * cos(m_direction);
        double yspeed = m_speed * sin(m_direction);
        m_direction += interval *0.0003;
        m_x += xspeed * interval;
        m_y += yspeed * interval;
        if (m_x < -1.0 || m_x > 1.0 || m_y < -1.0 || m_y > 1.0)
            init();
        if (rand() < RAND_MAX / 100)
            init();
       
    }

}