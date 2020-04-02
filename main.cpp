#include "SDLWrappers.cpp"
#include "EventLoop.cpp"

int main(void) {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		logSDLError();
		return -1;
	}

	if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError();
		SDL_Quit();
		return -1;
	}
	
	SDL_Window* win;
	SDL_Renderer* ren;
	
	if(!(win = SDL_CreateWindow("2D-Minecraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenResX, screenResY, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL))) {
		logSDLError();
		SDL_Quit();
		return -1;
	}
	
	if(!(ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
		logSDLError();
		SDL_DestroyWindow(win);
		SDL_Quit();
		return -1;
	}
	
	EventLoop();
	
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	IMG_Quit();
	SDL_Quit();
	return 0;
}