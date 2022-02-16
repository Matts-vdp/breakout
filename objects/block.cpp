#pragma once
#include <list>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// used to represent a rectangle on the screen
class Block {
	public: 
        SDL_FRect *rect = new SDL_FRect;
        Uint8 r,g,b;
		Block(int x, int y, int width, int height, Uint8 cr, Uint8 cg, Uint8 cb);
        Block(int x, int y, int width, int height) : Block(x,y,width,height, 0,150,150){};
		void render(SDL_Renderer *ren);
};

Block::Block(int x, int y, int width, int height, Uint8 cr, Uint8 cg, Uint8 cb) {
	rect->h = height;
	rect->w = width;
	rect->x = x;
	rect->y = y;
    r = cr;
    g = cg;
    b = cb;
}

// draw block to screen
void Block::render(SDL_Renderer *ren) {
	SDL_SetRenderDrawColor(ren, r,g,b,255);
	SDL_RenderFillRectF(ren, rect);
}
