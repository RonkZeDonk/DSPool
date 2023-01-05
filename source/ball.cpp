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
    this->xPos += this->xVel;
    this->yPos += this->yVel;

    if (this->xVel > 0) {
        this->xVel -= DELTA_VEL;
    } else if (this->xVel < 0) {
        this->xVel += DELTA_VEL;
    }

    if (this->yVel > 0) {
        this->yVel -= DELTA_VEL;
    } else if (this->yVel < 0) {
        this->yVel += DELTA_VEL;
    }

    // If the distance between velocity and 0 then we will see an infinite loop
    // where the velocities jump between a number < and > 0.
    //
    // Fixed here by clamping the values to 0 when it gets close.
    if (abs(this->xVel) < DELTA_VEL) { this->xVel = 0; }
    if (abs(this->yVel) < DELTA_VEL) { this->yVel = 0; }

    // Clamp balls to the inside of the pool table and flip their velocities
    // TODO check if behaviour produced if natural-looking
    if (this->xPos < 15)  {
        this->xPos = 15;
        this->xVel *= -1;
    }
    if (this->yPos < 15)  {
        this->yPos = 15;
        this->yVel *= -1;
    }
    if (this->xPos > 229) {
        this->xPos = 229;
        this->xVel *= -1;
    }
    if (this->yPos > 165) {
        this->yPos = 165;
        this->yVel *= -1;
    }
}

void Ball::renderBall() {
    glSprite(this->xPos, this->yPos, GL_FLIP_NONE, this->sprite);
}
