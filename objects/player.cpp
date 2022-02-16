#include "block.cpp"

// represents player rectangle
class Player : public Block {
    public:
        void handleEvent(SDL_Event& e);
        static constexpr float SPEED = 300;
        void move(float timestep);
        bool checkCollision(Block block, float timestep);
        void checkWall();
        bool collidesX(SDL_FRect *other, float timestep);
        bool collidesY(SDL_FRect *other, float timestep);
        Player(int x, int y, int width, int height);
        float vx;
};

Player::Player(int x, int y, int width, int height) : Block(x,y,width,height, 255,255,255) {
    vx = 0;
}

// updates the player location
void Player::move(float timestep) {
	rect->x += vx * timestep;
}

// moves the player according the pressed key
void Player::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_LEFT: vx -= SPEED; break;
			case SDLK_RIGHT: vx += SPEED; break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_LEFT: vx += SPEED; break;
			case SDLK_RIGHT: vx -= SPEED; break;
		}
	}
}

// limits the movement to the screen
void Player::checkWall(){
    if (rect->x < 0) { 
        rect->x = 0;
    }
    if (rect->x+rect->w > SCREEN_WIDTH) {
        rect->x = SCREEN_WIDTH - rect->w;
    }
}