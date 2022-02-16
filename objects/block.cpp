#pragma once
#include <list>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Block {
	public: 
		Block(int x, int y, int width, int height, Uint8 cr, Uint8 cg, Uint8 cb);
        Block(int x, int y, int width, int height) : Block(x,y,width,height, 0,150,150){};
		void render(SDL_Renderer *ren);
        SDL_FRect *rect = new SDL_FRect;
        Uint8 r,g,b;
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

void Block::render(SDL_Renderer *ren) {
	SDL_SetRenderDrawColor(ren, r,g,b,255);
	SDL_RenderFillRectF(ren, rect);
}
