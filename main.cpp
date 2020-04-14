#include "config.h"

#include "SDLWrappers.cpp"
#include "mainEventLoop.cpp"

int main(void) {
	// Initalize
	if(SDL_Init(SDL_INIT_VIDEO) != 0) { return -1; }
	
	// Create Window
	SDL_Window* win = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RESOLUTION_W, RESOLUTION_H, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!win) {
		logSDLError();
		SDL_Quit();
		return -1; 
	}
	
	// Create Renderer
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!ren) {
		logSDLError();
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return -1; 
	}
	
	// initialize SDL_Image for PNGs
	if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError();
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	
	// Main Loop
	mainEventLoop(ren);
	
	// Exit
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	IMG_Quit();
	SDL_Quit();
}