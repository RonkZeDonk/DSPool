#include <nds.h>
#include <gl2d.h>
#include <time.h>

#include "table.h"

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
    int angle = 0;

    // Sprites used in the table
    TableSprites sprites;

    // Used to see where the user is touching
    touchPosition touch;

    // Initalize bottom screen
    videoSetMode(MODE_5_3D);
    lcdMainOnBottom();
    glScreen2D();
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankE(VRAM_E_TEX_PALETTE);
    // --- end bottom screen init

    // Initalize top screen
    // Create a console for the top screen
    consoleDemoInit();
    // --- end top screen init

    // Seed rand
    srand(time(NULL));

    iprintf("\n");
    iprintf("         Current Table:        \n");
    iprintf("--------------------------------\n");

    // Create pool table
    PoolTable table = initTable(&sprites);

    while(1) {
        // Update the balls based on acumulated velocites
        updateTablePositions(&table);

        // Print out the ball positions
        printTable(table);

        // Show selected ball
        iprintf("\x1b[%d;0H>", selectedBall + 3);

        // Print out the user's touch values
        touchRead(&touch);
        iprintf("\x1b[21;0H\tTouch x = %04i, %04i\n", touch.rawx, touch.px);
        iprintf("\tTouch y = %04i, %04i\n", touch.rawy, touch.py);

        glBegin2D();
        {
            renderTable(&table, angle);
        }
        glEnd2D();

        // Clear the sprites before redrawing
        glFlush(0);

        // Wait for frame step (60 times per second)
        swiWaitForVBlank();

        // ---------------------
        // End of game loop area
        // ---------------------

        // Get the currently pressed keys
        scanKeys();
        int keys = keysHeld();
        int nonrepeatingKeysHeld = keysDownRepeat();

        // Exit the program if the start key is pressed
        if (keys & KEY_START) break;

        // TODO Remove debug statements
        if (nonrepeatingKeysHeld & KEY_SELECT) {
            setBalls(&table);
            angle = 0;
        }

        // TODO remove debug statements
        if (nonrepeatingKeysHeld & KEY_B && selectedBall > 0) selectedBall--;
        if (nonrepeatingKeysHeld & KEY_X && selectedBall < 15) selectedBall++;

        // TODO remove debug statements
        if (nonrepeatingKeysHeld & KEY_Y) {
            // Change velocity by -30 - 30 spaces
            for (int i = 0; i < 16; i++) {
                // 50% chance of moving the ball
                if (rand() % 2 == 0) {
                    ballRndMoveAmount = rand() % 60 - 30;
                    table.balls[i].xVel += ballRndMoveAmount;
                    table.balls[i].yVel += ballRndMoveAmount;
                }
            }
        }

        // TODO REMOVE
        if (keys & KEY_L) angle -= 100;
        if (keys & KEY_R) angle += 100;

        // TODO REMOVE: Move the currently selected ball
        if (keys & KEY_UP)    table.balls[selectedBall].y += -1;
        if (keys & KEY_DOWN)  table.balls[selectedBall].y += 1;
        if (keys & KEY_LEFT)  table.balls[selectedBall].x += -1;
        if (keys & KEY_RIGHT) table.balls[selectedBall].x += 1;
    }

    return 0;
}
