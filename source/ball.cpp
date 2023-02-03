#include "table.hpp"

Ball::Ball(Team team, glImage sprite[1], int xPos, int yPos) {
    this->team = team;

    this->sprite[0] = sprite[0];

    this->position.x = xPos;
    this->position.y = yPos;

    this->velocity.x = 0;
    this->velocity.y = 0;
}

void Ball::updateBallPosition() {
    const static int CONSERVED_ENERGY_PERCENT = 97;

    // Apply velocity
    this->position = this->position.plus(this->velocity);

    // Apply friction to the ball
    this->velocity.x = (this->velocity.x * CONSERVED_ENERGY_PERCENT) / 100;
    this->velocity.y = (this->velocity.y * CONSERVED_ENERGY_PERCENT) / 100;

    // Clamp balls to the inside of the pool table and flip their velocities
    // TODO(commit): properly give refund movement
    //                  - right now velocity is lost (apply CCD)
    if (this->position.x < inttof32(15)) {
        this->position.x = inttof32(15);
        this->velocity.x *= -1;
    }
    if (this->position.x > inttof32(230)) {
        this->position.x = inttof32(230);
        this->velocity.x *= -1;
    }
    if (this->position.y < inttof32(16)) {
        this->position.y = inttof32(16);
        this->velocity.y *= -1;
    }
    if (this->position.y > inttof32(166)) {
        this->position.y = inttof32(166);
        this->velocity.y *= -1;
    }
}

void Ball::renderBall() {
    glSprite(f32toint(this->position.x), f32toint(this->position.y), GL_FLIP_NONE, this->sprite);
}
