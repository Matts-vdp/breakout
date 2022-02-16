#include "block.cpp"

// represents the moving ball
class Ball : public Block {
    public:
        static constexpr float SPEED = 300;
        float vx, vy;
        Ball(int x, int y, int width, int height);
        void move(float timestep);
        bool checkCollision(Block block, float timestep);
        void checkWall();
        bool checkPlayer(Block block, float timestep);
        bool collides(SDL_FRect *other);
        bool collidesX(SDL_FRect *other, float timestep);
        bool collidesY(SDL_FRect *other, float timestep);
};

Ball::Ball(int x, int y, int width, int height) : Block(x,y,width,height, 255,255,255) {
    vx = SPEED*0.35;
	vy = -SPEED;
}

// Checks if the object overlaps with a rect
bool Ball::collides(SDL_FRect *other) {
    if ((rect->x > other->x && rect->x < other->x+other->w) || 
        (rect->x+rect->w > other->x && rect->x+rect->w < other->x+other->w)){
        if ((rect->y > other->y && rect->y < other->y+other->h) || 
            (rect->y+rect->h > other->y && rect->y+rect->h < other->y+other->h)){
            return true;
        }
    }
    return false;
}

// checks for a collision on the x axis
bool Ball::collidesX(SDL_FRect *other, float timestep) {
    rect->x += vx * timestep;
    bool res = collides(other);
    rect->x -= vx * timestep;
    return res;
}

// checks for a collision on the y axis
bool Ball::collidesY(SDL_FRect *other, float timestep) {
    rect->y += vy * timestep;
    bool res = collides(other);
    rect->y -= vy * timestep;
    return res;
}

// update position
void Ball::move(float timestep) {
	rect->x += vx * timestep;
	rect->y += vy * timestep;
}

// checks if the objects collide and adapts the velocity if needed
bool Ball::checkCollision(Block block, float timestep) {
    if (collidesY(block.rect, timestep)) {
        vy *= -1;
        rect->y += vy * timestep * 2;
        return true;
    }
    if (collidesX(block.rect, timestep)) {
        vx *= -1;
        rect->x += vx * timestep * 2;
        return true;
    }
    return false;
}

// collision with player
// changes the x velocity based on hit location
bool Ball::checkPlayer(Block block, float timestep) {
    if (collidesY(block.rect, timestep)) {
        rect->y += vy * timestep;
        float part = block.rect->w / 6;
        float off = rect->x - (block.rect->x-rect->w);
        vx = SPEED * (-1 + 0.33 * (int)(off/part));
        vy = -SPEED * (1-abs(-1 + 0.33 * (int)(off/part))*0.5);
        return true;
    }
    return false;
}

// bounce off walls
void Ball::checkWall(){
    if (rect->x < 0) { 
        rect->x = 0;
        vx *= -1;
    }
    if (rect->x+rect->w > SCREEN_WIDTH) {
        rect->x = SCREEN_WIDTH - rect->w;
        vx *= -1;
    }
    if (rect->y < 0) {
        rect->y = 0;
        vy *= -1;
    }
    if (rect->y+rect->h > SCREEN_HEIGHT) {
        rect->y = SCREEN_HEIGHT - rect->h;
        vy *= -1;
    }
}



