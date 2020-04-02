#include<iostream>
#include<cstdarg>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

void logSDLError(void){
	std::cerr << "[SDL Error]: " << SDL_GetError() << std::endl;
}

// Pass an asset to renderer of h x w at position (x,y)
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, unsigned int w, unsigned int h, int x, int y, SDL_Rect* clip = nullptr) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.h = h;
	dest.w = w;
	SDL_RenderCopy(renderer, texture, clip, &dest);
}
