#ifndef POOL_TABLE_INCLUDE
#define POOL_TABLE_INCLUDE

#include <nds.h>
#include <stdio.h>

// Position max (max num is this -1)
#define POS_MAX 51
// Radius of the pool balls
#define BALL_RADIUS 4
// Deceleration of the pool balls
#define DELTA_VEL 2

/**
 * Colours for pool balls
 */
typedef enum {
    Red, Blue
} BallColour;

/**
 * Pool ball struct
 */
typedef struct {
    // Ball colour
    BallColour colour;

    // Ball center x position
    int x;
    // Ball center y position
    int y;

    // Ball x velocity
    int xVel;
    // Ball y velocity
    int yVel;
} Ball;

/**
 * Pool table struct
 */
typedef struct {
    // Each pool table contains 15 balls
    Ball balls[15];
} PoolTable;

// ******************
// * BALL FUNCTIONS *
// ******************

/**
 * Initalize pool ball
 *
 * @param colour Ball colour
 * @param x x-position of the ball
 * @param y y-position of the ball
 *
 * @returns A constructed Ball
 */
Ball initBall(BallColour colour, int x, int y);

/**
 * Updates a ball's velocity based on a constant deceleration
 *
 * @param ball The ball to update
 */
void updateBallPosition(Ball* ball);

// *******************
// * TABLE FUNCTIONS *
// *******************

/**
 * Creates a classic pool table and sets the ball's coords accordingly
 */
PoolTable initTable();

/**
 * Randomizes the positions of a given pool table.
 *
 * @param table the memory address to the table which is to be randomized
 */
void randomizeBallPositions(PoolTable* table);

/**
 * Prints out the x and y coords of every ball in a table.
 */
void printTable(PoolTable table);

#endif // POOL_TABLE_INCLUDE
