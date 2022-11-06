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
    int ballRandomIndex;

    // Used to see where the user is touching
    touchPosition touch;

    videoSetModeSub(MODE_5_2D);
    vramSetBankC(VRAM_C_SUB_BG_0x06200000);
    vramSetBankD(VRAM_D_SUB_SPRITE);
    // set sprite mode
    oamInit(&oamSub, SpriteMapping_1D_128, false);

    // Set background
    int bg3 = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);

    dmaCopy(poolTable_imageBitmap, bgGetGfxPtr(bg3), poolTable_imageBitmapLen);
    dmaCopy(poolTable_imagePal, BG_PALETTE_SUB, poolTable_imagePalLen);

    // Ball sprite
    Ball tb = initBall(15, ColorTeam1, 229, 165);

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

        {
            // Print test ball's pos
            iprintf("\x1b[19;0H P(%6d,%6d)\tV(%3d,%3d)\n",
                    tb.x, tb.y, tb.xVel, tb.yVel
                    );
        }

        // Print out the user's touch values
        touchRead(&touch);
        iprintf("\x1b[21;0H\tTouch x = %04i, %04i\n", touch.rawx, touch.px);
        iprintf("\tTouch y = %04i, %04i\n", touch.rawy, touch.py);

        renderBall(&tb);
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
        // Key pressed was `A` then reroll the ball positions
        if (nonrepeatingKeysHeld & KEY_A) {
            randomizeBallPositions(&table);
        }

        // TODO remove debug statements
        if (nonrepeatingKeysHeld & KEY_B) {
            ballRandomIndex = rand() % 15;
            // Increase a random ball's velocity
            table.balls[ballRandomIndex].xVel -= rand() % 30;
            table.balls[ballRandomIndex].yVel -= rand() % 30;
        }

        // TODO remove debug statements
        if (nonrepeatingKeysHeld & KEY_X) {
            ballRandomIndex = rand() % 15;
            // Increase a random ball's velocity
            table.balls[ballRandomIndex].xVel += rand() % 30;
            table.balls[ballRandomIndex].yVel += rand() % 30;
        }

        if (keys & KEY_UP) tb.y += -1;
        if (keys & KEY_DOWN) tb.y += 1;
        if (keys & KEY_LEFT) tb.x += -1;
        if (keys & KEY_RIGHT) tb.x += 1;
    }

    return 0;
}
