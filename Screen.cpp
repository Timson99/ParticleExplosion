/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  File name     :  Screen.cpp
*  Purpose       :  Create a Particle Fire Simulation in SDL
*  @author       :  T. Herrmann
*  Date written  :  2018-05-15
*  Description   :  Screen Source File
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
#include "Screen.h"

using namespace std;

namespace shortcuts {

	const int Screen::SCREEN_WIDTH = 1280;
	const int Screen::SCREEN_HEIGHT = 720;
	const int Screen::TOTAL_PIXELS = SCREEN_HEIGHT * SCREEN_WIDTH;

	Screen::Screen(): m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_bufferBlur(NULL) {}

	bool Screen::initialize() {

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			cout << "FAILED to Initialize Video" << endl;
			cout << SDL_GetError() << endl;
			SDL_Quit();
			return false;
		}
		m_window = SDL_CreateWindow("SDL Demo", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP/*SDL_WINDOW_MAXIMIZED*/);

		if (m_window == NULL) {
			cout << "FAILED to Create Window" << endl;
			cout << SDL_GetError() << endl;
			SDL_Quit();
			return false;
		}
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

		if (m_renderer == NULL) {
			cout << "FAILED to Create Render" << endl;
			cout << SDL_GetError() << endl;
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (m_texture == NULL) {
			cout << "FAILED to Create Texture" << endl;
			cout << SDL_GetError() << endl;
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
		    return false;
		}
		m_buffer = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
        m_bufferBlur = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

		if (m_buffer == NULL || m_bufferBlur == NULL) {
			cout << "FAILED to Allocate Memory" << endl;
			cout << SDL_GetError() << endl;
			SDL_DestroyTexture(m_texture);
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return 4;
		}
		memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
        memset(m_bufferBlur, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		return true;

	}

    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
        /*memset(m_buffer, 220, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(char));
        m_buffer[60000] = 0xAA0000FF;

        for (int p = 0; p < TOTAL_PIXELS; p++) {
            m_buffer[p] = 0x24ffacff; }*/

        if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
            return;

        Uint32 color = 0;
        color += red;
        color <<= 8;
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF;
        
        m_buffer[SCREEN_WIDTH * y + x] = color;

        
    }

    void Screen::clearBuffers() {
        memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
        memset(m_bufferBlur, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    }

    void Screen::boxBlur() {
        // Swap the buffers, so pixel is in m_buffer2 and we are drawing to m_buffer1.
        Uint32 *temp = m_buffer;
        m_buffer = m_bufferBlur;
        m_bufferBlur = temp;
        for (int y = 0; y<SCREEN_HEIGHT; y++) {
            for (int x = 0; x<SCREEN_WIDTH; x++) {
                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;
                int adjacentCounter = 0;
                for (int row = -1; row <= 1; row++) {
                    for (int col = -1; col <= 1; col++) {
                        int currentX = x + col;
                        int currentY = y + row;
                        if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
                            Uint32 color = m_bufferBlur[currentY*SCREEN_WIDTH + currentX];
                            redTotal += (Uint8)(color >> 24);
                            greenTotal += (Uint8)(color >> 16);
                            blueTotal += (Uint8)(color >> 8);
                            adjacentCounter++;
                        }
                    }
                }
                Uint8 red = redTotal / adjacentCounter;
                Uint8 green = greenTotal / adjacentCounter;
                Uint8 blue = blueTotal / adjacentCounter;
                setPixel(x, y, red, green, blue);
            }
        }
    }

    void Screen::updateScreen() {
        SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
    }

    bool Screen::processEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event) == true) {
            if (event.type == SDL_QUIT) {
                return false;
            }
        }
        return true;
    }

	void Screen::screenExit() {

		delete[] m_buffer;
        delete[] m_bufferBlur;
		SDL_DestroyTexture(m_texture);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();

	}

}