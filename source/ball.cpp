#include "table.hpp"

Ball::Ball(Team team, glImage sprite[1], int xPos, int yPos) {
    this->team = team;

    this->sprite[0] = sprite[0];

    this->position.x = xPos;
    this->position.y = yPos;

    this->velocity.x = 0;
    this->velocity.y = 0;
}

void Ball::renderBall() {
    glSprite(f32toint(this->position.x), f32toint(this->position.y), GL_FLIP_NONE, this->sprite);
}
