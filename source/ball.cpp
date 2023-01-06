#include "table.hpp"

Ball::Ball(Team team, glImage sprite[1], int xPos, int yPos) {
    this->team = team;

    this->sprite[0] = sprite[0];

    this->xPos = xPos;
    this->yPos = yPos;

    this->xVel = 0;
    this->yVel = 0;
}

void Ball::updateBallPosition() {
    const static int CONSERVED_ENERGY_PERCENT = 97;

    // Apply velocity
    this->xPos += this->xVel;
    this->yPos += this->yVel;

    // Apply friction to the ball
    this->xVel = (this->xVel * CONSERVED_ENERGY_PERCENT) / 100;
    this->yVel = (this->yVel * CONSERVED_ENERGY_PERCENT) / 100;

    // Clamp balls to the inside of the pool table and flip their velocities
    if (this->xPos < inttof32(15)) {
        this->xPos = inttof32(15);
        this->xVel *= -1;
    }
    if (this->xPos > inttof32(229)) {
        this->xPos = inttof32(229);
        this->xVel *= -1;
    }
    if (this->yPos < inttof32(16)) {
        this->yPos = inttof32(16);
        this->yVel *= -1;
    }
    if (this->yPos > inttof32(165)) {
        this->yPos = inttof32(165);
        this->yVel *= -1;
    }
}

void Ball::renderBall() {
    glSprite(f32toint(this->xPos), f32toint(this->yPos), GL_FLIP_NONE, this->sprite);
}
