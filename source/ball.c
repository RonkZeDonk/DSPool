#include "table.h"

Ball initBall(int id, Team team, glImage sprite[1], int x, int y) {
    return (Ball){
        team,           // Ball's team
        { sprite[0] },  // Ball's graphics
        x, y,           // X and Y position of ball
        0, 0            // X and Y velocity of ball
    };
}

void updateBallPosition(Ball* ball) {
    ball->x += ball->xVel;
    ball->y += ball->yVel;

    if (ball->xVel > 0) {
        ball->xVel -= DELTA_VEL;
    } else if (ball->xVel < 0) {
        ball->xVel += DELTA_VEL;
    }

    if (ball->yVel > 0) {
        ball->yVel -= DELTA_VEL;
    } else if (ball->yVel < 0) {
        ball->yVel += DELTA_VEL;
    }

    // If the distance between velocity and 0 then we will see an infinite loop
    // where the velocities jump between a number < and > 0.
    //
    // Fixed here by clamping the values to 0 when it gets close.
    if (abs(ball->xVel) < DELTA_VEL) { ball->xVel = 0; }
    if (abs(ball->yVel) < DELTA_VEL) { ball->yVel = 0; }

    // Clamp balls to the inside of the pool table and flip their velocities
    // TODO check if behaviour produced if natural-looking
    if (ball->x < 15)  {
        ball->x = 15;
        ball->xVel *= -1;
    }
    if (ball->y < 15)  {
        ball->y = 15;
        ball->yVel *= -1;
    }
    if (ball->x > 229) {
        ball->x = 229;
        ball->xVel *= -1;
    }
    if (ball->y > 165) {
        ball->y = 165;
        ball->yVel *= -1;
    }
}

void renderBall(Ball* ball) {
    glSprite(ball->x, ball->y, GL_FLIP_NONE, ball->sprite);
}
