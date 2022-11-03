#include "nds/arm9/background.h"
#include "nds/arm9/video.h"
#include "nds/dma.h"
#include "nds/interrupts.h"
#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "nds/timers.h"
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
    int ballRandomIndex;
    int moveBy = 50;

    // Top screen
    // -------------------------

    // Create a console for the top screen
    PrintConsole topScreen;
    videoSetMode(MODE_0_2D);
    vramSetBankA(VRAM_A_MAIN_BG);
    consoleInit(&topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

    // Use main (top; idk if this is main screen) screen console
    consoleSelect(&topScreen);

    // Seed rand
    srand(time(NULL));

    iprintf("\n         Current Table\n");
    iprintf("--------------------------------\n");

    // Create pool table
    PoolTable table = initTable();

   // Display table
    printTable(table);

    // Bottom Screen
    // -------------------------

    // Used to see where the user is touching
    touchPosition touch;

    videoSetModeSub(MODE_5_2D);
    //vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG_0x06200000);

    int bg3 = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);

    dmaCopy(poolTable_imageBitmap, bgGetGfxPtr(bg3), 256*256);
    dmaCopy(poolTable_imagePal, BG_PALETTE_SUB, 256*2);

    while(1) {
        for (int i = 0; i < 15; i++) {
            if (table.balls[i].xVel != 0 || table.balls[i].yVel != 0) {
                updateBallPosition(&table.balls[i]);
            }
        }

        {
            // Print out the ball positions
            iprintf("\x1b[3;0H");
            printTable(table);
            iprintf("--------------------------------\n");
        }

        // Print out the user's touch values
        touchRead(&touch);
        iprintf("\x1b[21;0H\tTouch x = %04i, %04i\n", touch.rawx, touch.px);
        iprintf("\tTouch y = %04i, %04i\n", touch.rawy, touch.py);

        // ---------------------
        // End of game loop area
        // ---------------------

        // Wait for frame step (60 times per second)
        swiWaitForVBlank();

        // Get the currently pressed keys
        scanKeys();

        // Exit the program if the start key is pressed
        if (keysDown() & KEY_START) break;

        // TODO Remove debug statements
        // Key pressed was `A` then reroll the ball positions
        if (keysDown() & KEY_A) {
            randomizeBallPositions(&table);
        }

        // TODO remove debug statements
        if (keysDown() & KEY_B) {
            ballRandomIndex = rand() % 15;
            // Increase a random ball's velocity
            table.balls[ballRandomIndex].xVel -= moveBy;
            table.balls[ballRandomIndex].yVel -= moveBy + 1;
        }

        // TODO remove debug statements
        if (keysDown() & KEY_X) {
            ballRandomIndex = rand() % 15;
            // Increase a random ball's velocity
            table.balls[ballRandomIndex].xVel += moveBy;
            table.balls[ballRandomIndex].yVel += moveBy + 1;
        }
    }

    return 0;
}
