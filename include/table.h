#ifndef POOL_TABLE_INCLUDE
#define POOL_TABLE_INCLUDE

#include <nds.h>
#include <gl2d.h>
#include <stdio.h>

#include "ball.h"

// Position max (max num is this -1)
#define POS_MAX 51
// Radius of the pool balls
#define BALL_RADIUS 4
// Deceleration of the pool balls
#define DELTA_VEL 2

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

/**
 * Pool table struct
 */
typedef struct {
    // Each pool table contains 15 balls
    Ball balls[16];

    // Sprites
    TableSprites* sprites;
} PoolTable;

// *******************
// * TABLE FUNCTIONS *
// *******************

/**
 * Creates a classic pool table and sets the ball's coords accordingly
 */
PoolTable initTable(TableSprites* sprites);

/**
 * Loads the table's sprites
 */
void loadTableSprites(TableSprites* sprites);

/**
 * Set balls on table
 *
 * @param table The table which is to be set
 */
void setBalls(PoolTable* table);

/**
 * Render all the balls on the table
 *
 * @param table The table to render
 * @param angle The angle to display the cue at
 */
void renderTable(PoolTable* table, int angle);

/**
 * Update the positions of all the balls on the table
 */
void updateTablePositions(PoolTable* table);

/**
 * Prints out the x and y coords of every ball in a table.
 */
void printTable(PoolTable* table);

/**
 * Puts the cue on the screen
 *
 * Distance Range: Any number < 57 and not 0
 */
void renderCue(PoolTable* table, int distance, int angle);

#endif // POOL_TABLE_INCLUDE
