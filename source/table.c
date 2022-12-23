#include "table.h"
#include "nds/arm9/sprite.h"

#include "poolBall_image.h"

u16* ball_gfx_mem;

Ball initBall(int id, BallColour colour, int x, int y) {
    Ball ball = {
        id,     // Ball ID
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
    dmaCopy(poolBall_imageTiles, ball_gfx_mem, poolBall_imageTilesLen);

    oamSet(&oamSub, ball->id, ball->x, ball->y, 0, 0, SpriteSize_32x32,
            SpriteColorFormat_256Color, ball_gfx_mem, 0,
            false, false, false, false, false);
}

PoolTable initTable() {
    PoolTable table;

    for (int i = 0; i < 15; i++) {
        table.balls[i] = initBall(i, ColorTeam1, 0, 0 );
    };

    setBalls(&table);

    dmaCopy(poolBall_imagePal, SPRITE_PALETTE_SUB, poolBall_imagePalLen);
    // TODO make this not a global. a part of the table struct ideally
    ball_gfx_mem = oamAllocateGfx(&oamSub,
            SpriteSize_16x16, SpriteColorFormat_256Color);

    return table;
}

void setBalls(PoolTable *table) {
    // [ball id][x, y coords]
    int tableLUT[15][2] = {
        { 79, 87 }, { 69, 81 }, { 69, 93 },  // Balls 0-2
        { 59, 75 }, { 59, 87 }, { 59, 99 },  // Balls 3-5
        { 49, 69 }, { 49, 81 }, { 49, 93 },  // Balls 6-8
        { 49, 105 }, { 39, 63 }, { 39, 75 }, // Balls 9-11
        { 39, 87 }, { 39, 99 }, { 39, 111 }, // Balls 12-15
    };

    for (int i = 0; i < 15; i++) {
        table->balls[i].x = tableLUT[i][0];
        table->balls[i].y = tableLUT[i][1];
    }
}

void renderTable(PoolTable* table) {
    for (int i = 0; i < 15; i++) {
        renderBall(&table->balls[i]);
    }
}

void printTable(PoolTable table) {
    iprintf("\x1b[3;0H");
    for (int i = 0; i < 15; i++) {
        iprintf(" P(%6d,%6d)\tV(%3d,%3d)\n",
                table.balls[i].x,
                table.balls[i].y,

                table.balls[i].xVel,
                table.balls[i].yVel
                );
        iprintf("                               \r");
    }
    iprintf("--------------------------------\n");
}

