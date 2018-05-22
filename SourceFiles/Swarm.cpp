/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  File name     :  Swarm.cpp
*  Purpose       :  Create a Particle Fire Simulation in SDL
*  @author       :  T. Herrmann
*  Date written  :  2018-05-20
*  Description   :  Swarm Source File
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
#include "Swarm.h"
using namespace std;

namespace shortcuts {

    const int Swarm::NPARTICLES = 5000;

    Swarm::Swarm(): lastUpdate(0) {
        m_pParticles = new Particle[NPARTICLES];
    }

    void Swarm::update(int elapsed) {
        int interval = elapsed - lastUpdate;
        for (int i = 0; i < NPARTICLES; i++) {
            m_pParticles[i].update(interval);
        }

        lastUpdate = elapsed;

    }

    Swarm::~Swarm() {
        delete[] m_pParticles;
    }


}