#include "table.h"
#include "nds/arm9/sprite.h"

#include "poolBall_image.h"

u16* ball_gfx_mem;

PoolTable initTable() {
    PoolTable table;

    dmaCopy(poolBall_imagePal, SPRITE_PALETTE_SUB, poolBall_imagePalLen);
    ball_gfx_mem = oamAllocateGfx(&oamSub,
            SpriteSize_16x16, SpriteColorFormat_256Color);

    for (int i = 0; i < 15; i++) {
        table.balls[i] = initBall(i, ColorTeam1, ball_gfx_mem, 0, 0);
    };

    setBalls(&table);

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

