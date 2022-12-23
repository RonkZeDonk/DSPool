#include "nds/arm9/background.h"
#include "nds/arm9/input.h"
#include "nds/arm9/sprite.h"
#include "nds/arm9/video.h"
#include "nds/dma.h"
#include "nds/interrupts.h"
#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "nds/timers.h"
#include "poolBall_image.h"
#include "table.h"

#include "poolTable_image.h"

/**
 * Puts the DS' thread to sleep for n frames
 */
void sleepForNFrames(int frames) {
    for (int i = 0; i < frames; i++) {
        swiWaitForVBlank();
    }
}

/**
 * Puts the DS' thread to sleep for n seconds
 */
void sleepForSec(int seconds) {
    sleepForNFrames(60 * seconds);
}


//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
    int ballRndMoveAmount;
    int selectedBall = 0;

    // Used to see where the user is touching
    touchPosition touch;


    // Initalize bottom screen
    videoSetModeSub(MODE_5_2D);
    vramSetBankC(VRAM_C_SUB_BG_0x06200000);
    vramSetBankD(VRAM_D_SUB_SPRITE);

    // Set sprite mode
    oamInit(&oamSub, SpriteMapping_1D_128, false);

    // Set background
    int bg3 = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
    dmaCopy(poolTable_imageBitmap, bgGetGfxPtr(bg3), poolTable_imageBitmapLen);
    dmaCopy(poolTable_imagePal, BG_PALETTE_SUB, poolTable_imagePalLen);
    // --- end bottom screen init

    // Initalize top screen
    // Create a console for the top screen
    PrintConsole topScreen;
    videoSetMode(MODE_0_2D);
    vramSetBankA(VRAM_A_MAIN_BG);
    consoleInit(&topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

    // Put console on the top screen
    consoleSelect(&topScreen);
    // --- end top screen init

    // Seed rand
    srand(time(NULL));

    iprintf("\n");
    iprintf("         Current Table:        \n");
    iprintf("--------------------------------\n");

    // Create pool table
    PoolTable table = initTable();

    while(1) {
        // TODO move this into it's own function in table.c
        for (int i = 0; i < 15; i++) {
            if (table.balls[i].xVel != 0 || table.balls[i].yVel != 0) {
                updateBallPosition(&table.balls[i]);
            }
        }

        // Print out the ball positions
        printTable(table);

        // Show selected ball
        iprintf("\x1b[%d;0H>", selectedBall + 3);

        // Print out the user's touch values
        touchRead(&touch);
        iprintf("\x1b[21;0H\tTouch x = %04i, %04i\n", touch.rawx, touch.px);
        iprintf("\tTouch y = %04i, %04i\n", touch.rawy, touch.py);

        renderTable(&table);

        // ---------------------
        // End of game loop area
        // ---------------------

        // Wait for frame step (60 times per second)
        swiWaitForVBlank();

        // Flush OAM (basically clear the sprites before redrawing)
        oamUpdate(&oamSub);

        // Get the currently pressed keys
        scanKeys();
        int keys = keysHeld();
        int nonrepeatingKeysHeld = keysDownRepeat();

        // Exit the program if the start key is pressed
        if (keys & KEY_START) break;

        // TODO Remove debug statements
        // Key pressed was `A` then move balls back to default place
        if (nonrepeatingKeysHeld & KEY_A) {
            setBalls(&table);
        }

        // TODO remove debug statements
        if (nonrepeatingKeysHeld & KEY_B) {
            ballRndMoveAmount = rand() % 30;
            // Increase a random ball's velocity
            table.balls[selectedBall].xVel -= ballRndMoveAmount;
            table.balls[selectedBall].yVel -= ballRndMoveAmount;
        }

        // TODO remove debug statements
        if (nonrepeatingKeysHeld & KEY_X) {
            ballRndMoveAmount = rand() % 30;
            // Increase a random ball's velocity
            table.balls[selectedBall].xVel += ballRndMoveAmount;
            table.balls[selectedBall].yVel += ballRndMoveAmount;
        }

        // TODO remove debug statements
        if (nonrepeatingKeysHeld & KEY_Y) {
            // Change velocity by -30 - 30 spaces
            for (int i = 0; i < 15; i++) {
                // 50% chance of moving the ball
                if (rand() % 2 == 0) {
                    ballRndMoveAmount = rand() % 60 - 30;
                    table.balls[i].xVel += ballRndMoveAmount;
                    table.balls[i].yVel += ballRndMoveAmount;
                }
            }
        }

        // TODO REMOVE: Change currently selected ball
        if (nonrepeatingKeysHeld & KEY_L && selectedBall > 0) selectedBall--;
        if (nonrepeatingKeysHeld & KEY_R && selectedBall < 14) selectedBall++;

        // TODO REMOVE: Move the currently selected ball
        if (keys & KEY_UP)    table.balls[selectedBall].y += -1;
        if (keys & KEY_DOWN)  table.balls[selectedBall].y += 1;
        if (keys & KEY_LEFT)  table.balls[selectedBall].x += -1;
        if (keys & KEY_RIGHT) table.balls[selectedBall].x += 1;
    }

    return 0;
}
