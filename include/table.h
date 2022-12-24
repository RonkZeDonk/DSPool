#ifndef POOL_TABLE_INCLUDE
#define POOL_TABLE_INCLUDE

#include <nds.h>
#include <stdio.h>

#include "ball.h"

// Position max (max num is this -1)
#define POS_MAX 51
// Radius of the pool balls
#define BALL_RADIUS 4
// Deceleration of the pool balls
#define DELTA_VEL 2

/**
 * Pool table struct
 */
typedef struct {
    // Each pool table contains 15 balls
    Ball balls[15];

 //   u16* ball_sprite_mem;
} PoolTable;

// *******************
// * TABLE FUNCTIONS *
// *******************

/**
 * Creates a classic pool table and sets the ball's coords accordingly
 */
PoolTable initTable();

/**
 * Set balls on table
 *
 * @param table The table which is to be set
 */
void setBalls(PoolTable *table);

/**
 * Render all the balls on the table
 *
 * @param table The table to render
 */
void renderTable(PoolTable* table);

/**
 * Prints out the x and y coords of every ball in a table.
 */
void printTable(PoolTable table);

#endif // POOL_TABLE_INCLUDE
