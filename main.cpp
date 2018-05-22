/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  File name     :  main.cpp
 *  Purpose       :  Create a Particle Fire Simulation in SDL
 *  @author       :  T. Herrmann
 *  Date written  :  2018-05-11
 *  Description   :  Main Program Source File
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
#include <cstdlib>
#include <ctime>
#include "Screen.h"
#include "Particle.h"
#include "Swarm.h"

using namespace std;
using namespace shortcuts;

int main(int argc, char** argv) {

    Screen scr;
    if(scr.initialize() == false)
        return 1;

    srand((unsigned int)time(NULL));
    Swarm swarm;

    while (true) { //GUI Event Loop
        int elapsed = SDL_GetTicks();
        //scr.clearBuffers();
        swarm.update(elapsed);
        unsigned char red = (unsigned char)((1 + cos(elapsed * 0.0007)) * 127.5);
        unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0004)) * 127.5);
        unsigned char blue = (unsigned char)((1 + cos(elapsed * 0.0005)) * 127.5);

        /*for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
            for (int x = 0; x< Screen::SCREEN_WIDTH; x++) {
                scr.setPixel( x , y , red , green , blue);
        }
         */
        const Particle* const pParticles = swarm.getParticles();

        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];
            int x = (int)((particle.m_x + 1) * Screen::SCREEN_WIDTH/2);
            int y = (int)(particle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2);
            scr.setPixel(x, y, red, green, blue);
        }
        
        scr.boxBlur();
        scr.updateScreen();
        if (scr.processEvents() == false)
            break;
    }
    
    scr.screenExit();
	return 0;
}