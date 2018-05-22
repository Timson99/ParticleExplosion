#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

namespace shortcuts {
	class Screen {
	
	public: 
		const static int SCREEN_WIDTH;
		const static int SCREEN_HEIGHT;
        const static int TOTAL_PIXELS;

	private:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_texture;
		Uint32* m_buffer;
        Uint32* m_bufferBlur;

	public:
		Screen();
		bool initialize();
        void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
        void clearBuffers();
        void boxBlur();
        void updateScreen();
		bool processEvents();
		void screenExit();

	};
}
#endif 