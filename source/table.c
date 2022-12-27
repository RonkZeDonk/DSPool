#include "table.h"

#include "poolBallA_image.h"
#include "poolBallB_image.h"
#include "cueBall_image.h"
#include "cueStick_image.h"
#include "blackBall_image.h"
#include "poolTable_image.h"

PoolTable initTable(TableSprites* sprites) {
    PoolTable table;

    loadTableSprites(sprites);
    table.sprites = sprites;

    for (int i = 0; i < 16; i++) {
        if (i == 0) {
            table.balls[i] = initBall(i, BlackBall, sprites->blackBall, 0, 0);
        } else if (i == 15) {
            table.balls[i] = initBall(i, CueBall, sprites->cueBall, 0, 0);
        } else if (i % 2 == 0) {
            table.balls[i] = initBall(i, TeamA, sprites->ballA, 0, 0);
        } else {
            table.balls[i] = initBall(i, TeamB, sprites->ballB, 0, 0);
        }
    };

    setBalls(&table);

    return table;
}

void loadTableSprites(TableSprites* sprites) {
    glLoadTileSet(
            sprites->background,
            256, 256, 256, 256,
            GL_RGB256,
            TEXTURE_SIZE_256, TEXTURE_SIZE_256,
            GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF |
                GL_TEXTURE_COLOR0_TRANSPARENT,
            256,
            (u16*) poolTable_imagePal,
            (u8*)  poolTable_imageBitmap
        );
    glLoadTileSet(
            sprites->ballA,
            32, 32, 32, 32,
            GL_RGB16,
            TEXTURE_SIZE_32, TEXTURE_SIZE_32,
            GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF |
                GL_TEXTURE_COLOR0_TRANSPARENT,
            16,
            (u16*) poolBallA_imagePal,
            (u8*)  poolBallA_imageBitmap
        );
    glLoadTileSet(
            sprites->ballB,
            32, 32, 32, 32,
            GL_RGB16,
            TEXTURE_SIZE_32, TEXTURE_SIZE_32,
            GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF |
                GL_TEXTURE_COLOR0_TRANSPARENT,
            16,
            (u16*) poolBallB_imagePal,
            (u8*)  poolBallB_imageBitmap
        );
    glLoadTileSet(
            sprites->blackBall,
            32, 32, 32, 32,
            GL_RGB16,
            TEXTURE_SIZE_32, TEXTURE_SIZE_32,
            GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF |
                GL_TEXTURE_COLOR0_TRANSPARENT,
            16,
            (u16*) blackBall_imagePal,
            (u8*)  blackBall_imageBitmap
        );
    glLoadTileSet(
            sprites->cueBall,
            32, 32, 32, 32,
            GL_RGB16,
            TEXTURE_SIZE_32, TEXTURE_SIZE_32,
            GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF |
                GL_TEXTURE_COLOR0_TRANSPARENT,
            16,
            (u16*) cueBall_imagePal,
            (u8*)  cueBall_imageBitmap
        );
    glLoadTileSet(
            sprites->cueStick,
            128, 32, 128, 32,
            GL_RGB16,
            TEXTURE_SIZE_128, TEXTURE_SIZE_32,
            GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF |
                GL_TEXTURE_COLOR0_TRANSPARENT,
            16,
            (u16*) cueStick_imagePal,
            (u8*)  cueStick_imageBitmap
        );
}

void setBalls(PoolTable *table) {
    // [ball id][x, y coords]
    int tableLUT[15][2] = {
        { 59, 87 }, { 69, 81 }, { 69, 93 },  // Balls 0-2
        { 39, 111 }, { 79, 87 }, { 59, 99 },  // Balls 3-5
        { 49, 81 }, { 49, 69 }, { 49, 105 },  // Balls 6-8
        { 49, 93 }, { 59, 75 }, { 39, 75 }, // Balls 9-11
        { 39, 87 }, { 39, 99 }, { 39, 63 }, // Balls 12-15
    };

    for (int i = 0; i < 15; i++) {
        table->balls[i].x = tableLUT[i][0];
        table->balls[i].y = tableLUT[i][1];
    }

    // Set cue ball
    table->balls[15].x = 150;
    table->balls[15].y = 87;
}

void renderTable(PoolTable* table, int angle) {
    // Render table background
    glSprite(0, 0, GL_FLIP_NONE, table->sprites->background);

    // Render each ball
    for (int i = 0; i < 16; i++) {
        renderBall(&table->balls[i]);
    }

    // Render cue stick
    renderCue(table, 30, angle);
}

void updateTablePositions(PoolTable* table) {
    for (int i = 0; i < 16; i++) {
        if (table->balls[i].xVel != 0 || table->balls[i].yVel != 0) {
            updateBallPosition(&table->balls[i]);
        }
    }
}

void printTable(PoolTable table) {
    iprintf("\x1b[3;0H");
    for (int i = 0; i < 16; i++) {
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

void renderCue(PoolTable* table, int distance, int angle) {
    const int angleMultiplier = 20;
    const int centreOffset = 6;

    // Straighten cue
    angle += 620;

    int x = table->balls[15].x;
    int y = table->balls[15].y;
    int beta = angle - (angleMultiplier * distance);

    glSpriteRotate(
            (x + centreOffset) + (cosLerp(angle) / distance),
            (y + centreOffset) + (sinLerp(angle) / distance),
            beta,
            GL_FLIP_NONE, table->sprites->cueStick
        );
}
