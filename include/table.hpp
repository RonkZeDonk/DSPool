#ifndef POOL_TABLE_INCLUDE
#define POOL_TABLE_INCLUDE

#include <nds.h>
#include <gl2d.h>
#include <stdio.h>

#include "ball.hpp"

/**
 * The sprites that the table can render
 */
typedef struct {
    glImage background[1];
    glImage ballA[1];
    glImage ballB[1];
    glImage cueBall[1];
    glImage cueStick[1];
    glImage blackBall[1];
} TableSprites;

class PoolTable {
    public:
        // Each pool table contains 15 balls
        Ball balls[16];

        // Sprites
        TableSprites* sprites;

        // Cuestick angle
        int cuestickAngle;

        // ---- FUNCTIONS ----

        /**
         * Creates a classic pool table and sets the ball's coords accordingly
         */
        PoolTable();

        // TODO: Destructor
        ~PoolTable() {};

        /**
         * Loads the table's sprites
         */
        void loadTableSprites();

        /**
         * Set balls on table
         */
        void setBalls();

        /**
         * Render all the balls on the table
         */
        void renderTable();

        /**
         * Update the positions of all the balls on the table
         */
        void updateTablePositions();

        /**
         * Prints out the x and y coords of every ball in a table.
         */
        void printTable();

        /**
         * Puts the cue on the screen
         *
         * @param distance distance from the ball (range 1-57)
         */
        void renderCue(int distance);
};

void drawDottedLine(Vector2D* p1, Vector2D* p2, int color, int numOfDots);

#endif // POOL_TABLE_INCLUDE
