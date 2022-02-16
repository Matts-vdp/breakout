#include <SDL2/SDL.h>
#include <stdio.h>
#include <list>

#include "objects/block.cpp"
#include "objects/ball.cpp"
#include "objects/player.cpp"

//Screen dimension constants


std::list<Block> initBlocks(){
	std::list<Block> l;
	int pad = 10;
	int wb = 6;
	int hb = 5;
	int width = (SCREEN_WIDTH-wb*pad)/wb;
	int height = ((SCREEN_HEIGHT/8*3)-hb*pad)/hb;
	for (int x=0; x<wb; x++) {
		for (int y=0; y<hb; y++) {
			l.push_back(Block(pad*(x+1) + (width*x), pad*(y+1) + (height*y), width, height));
		}
	}
	return l;
}

void gameloop(SDL_Renderer *ren) {
	bool quit = false;
	SDL_Event e;
	Ball ball((SCREEN_WIDTH-7)/2,SCREEN_HEIGHT/4*3,15,15);
	Player player((SCREEN_WIDTH-150)/2,SCREEN_HEIGHT-20*2,150,10);
	std::list<Block> blocks = initBlocks();

	Uint64 time = SDL_GetTicks64();

	while (!quit) {
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				quit = true;
			}
			player.handleEvent(e);
		}
		Uint64 newtime = SDL_GetTicks64();
		float timestep = (newtime-time)/1000.f;

		player.move(timestep);
		player.checkWall();

		ball.move(timestep);
		for (std::list<Block>::iterator i=blocks.begin(); i!=blocks.end(); i++) {
			 if (ball.checkCollision(*i, timestep)){
				 blocks.erase(i);
			 }
		}
		ball.checkPlayer(player, timestep);
		ball.checkWall();
		
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);

		player.render(ren);
		ball.render(ren);
		for (Block b: blocks) {
			b.render(ren);
		}
		
		SDL_RenderPresent(ren);
		SDL_Delay(5);
		time = newtime;
	}
}


int main( int argc, char* args[] )
{
	SDL_Window* window = NULL;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return 1;
	}

	//Create window
	window = SDL_CreateWindow( "Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
	gameloop(ren);	
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}