#include "table.h"

Ball initBall(BallColour colour, int x, int y) {
    Ball ball = {
        colour, // Ball colour
        x, y,   // Positions
        0, 0    // Velocities
    };

    return ball;
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
}

PoolTable initTable() {
    PoolTable table;

    // TODO Properly initilize the table + coords
    for (int i = 0; i < 15; i++) {
        table.balls[i] = initBall(Red, rand() % POS_MAX, rand() % POS_MAX);
    };

    return table;
}

void randomizeBallPositions(PoolTable* table) {
    for (int i = 0; i < 15; i++) {
        table->balls[i].x = rand() % POS_MAX;
        table->balls[i].y = rand() % POS_MAX;
    }
}

void printTable(PoolTable table) {
    for (int i = 0; i < 15; i++) {
        iprintf(" P(%6d,%6d)\tV(%3d,%3d)\n",
                table.balls[i].x,
                table.balls[i].y,

                table.balls[i].xVel,
                table.balls[i].yVel
                );
        iprintf("                               \r");
    }
}

