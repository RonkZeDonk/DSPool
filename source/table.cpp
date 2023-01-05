#include "table.hpp"

#include "poolBallA_image.h"
#include "poolBallB_image.h"
#include "cueBall_image.h"
#include "cueStick_image.h"
#include "blackBall_image.h"
#include "poolTable_image.h"

PoolTable::PoolTable() {
    this->loadTableSprites();

    for (int i = 0; i < 16; i++) {
        if (i == 0) {
            this->balls[i] = *new Ball(Team::BlackBall, sprites->blackBall, 0, 0);
        } else if (i == 15) {
            this->balls[i] = *new Ball(Team::CueBall, sprites->cueBall, 0, 0);
        } else if (i % 2 == 0) {
            this->balls[i] = *new Ball(Team::TeamA, sprites->ballA, 0, 0);
        } else {
            this->balls[i] = *new Ball(Team::TeamB, sprites->ballB, 0, 0);
        }
    };

    this->setBalls();
}

void PoolTable::loadTableSprites() {
    glLoadTileSet(
            this->sprites->background,
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
            this->sprites->ballA,
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
            this->sprites->ballB,
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
            this->sprites->blackBall,
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
            this->sprites->cueBall,
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
            this->sprites->cueStick,
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

void PoolTable::setBalls() {
    // [ball id][x, y coords]
    int tableLUT[16][2] = {
        { 59, 87 }, { 69, 81 }, { 69, 93 },  // Balls 0-2
        { 39, 111 }, { 79, 87 }, { 59, 99 }, // Balls 3-5
        { 49, 81 }, { 49, 69 }, { 49, 105 }, // Balls 6-8
        { 49, 93 }, { 59, 75 }, { 39, 75 },  // Balls 9-11
        { 39, 87 }, { 39, 99 }, { 39, 63 },  // Balls 12-15
        { 150, 87 }                          // Cueball
    };

    for (int i = 0; i < 16; i++) {
        this->balls[i].xPos = tableLUT[i][0];
        this->balls[i].yPos = tableLUT[i][1];
    }

    this->cuestickAngle = 0;
}

void PoolTable::renderTable() {
    // Render table background
    glSprite(0, 0, GL_FLIP_NONE, this->sprites->background);

    // Render each ball
    for (int i = 0; i < 16; i++) {
        this->balls[i].renderBall();
    }

    // Render cue stick
    this->renderCue(30);
}

void PoolTable::updateTablePositions() {
    for (int i = 0; i < 16; i++) {
        if (this->balls[i].xVel != 0 || this->balls[i].yVel != 0) {
            this->balls[i].updateBallPosition();
        }
    }
}

void PoolTable::printTable() {
    iprintf("\x1b[3;0H");
    for (int i = 0; i < 16; i++) {
        iprintf(" P(%6d,%6d)\tV(%3d,%3d)\n",
                this->balls[i].xPos,
                this->balls[i].yPos,

                this->balls[i].xVel,
                this->balls[i].yVel
                );
        iprintf("                               \r");
    }
    iprintf("--------------------------------\n");
}

void PoolTable::renderCue(int distance) {
    const int ANGLE_MULTIPLIER = 20;
    const int CENTRE_OFFSET = 6;

    // Straighten cue
    this->cuestickAngle += 620;

    int x = this->balls[15].xPos;
    int y = this->balls[15].yPos;
    int angle = this->cuestickAngle - (ANGLE_MULTIPLIER * distance);

    glSpriteRotate(
            (x + CENTRE_OFFSET) + (cosLerp(this->cuestickAngle) / distance),
            (y + CENTRE_OFFSET) + (sinLerp(this->cuestickAngle) / distance),
            angle,
            GL_FLIP_NONE, this->sprites->cueStick
        );

    // Reset cuestick angle
    this->cuestickAngle -= 620;
}
