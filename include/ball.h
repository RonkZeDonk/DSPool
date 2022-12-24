#ifndef POOL_BALL_INCLUDE
#define POOL_BALL_INCLUDE

#include <nds.h>
#include <stdio.h>

/**
 * Colours for pool balls
 */
typedef enum {
    ColorTeam1,
    ColorTeam2,
} BallColour;

/**
 * Pool ball struct
 */
typedef struct {
    // Ball's ID. Used in OAM
    int id;

    // Ball colour
    BallColour colour;

    // Pointer to the ball's graphics
    u16* gfx_mem;

    // Ball center x position
    int x;
    // Ball center y position
    int y;

    // Ball x velocity
    int xVel;
    // Ball y velocity
    int yVel;
} Ball;

// ******************
// * BALL FUNCTIONS *
// ******************

/**
 * Initalize pool ball
 *
 * @param id Ball's ID. Used in the OAM
 * @param colour Ball colour
 * @param gfx_mem Pointer to the ball's graphics memory
 * @param x x-position of the ball
 * @param y y-position of the ball
 *
 * @returns A constructed Ball
 */
Ball initBall(int id, BallColour colour, u16* gfx_mem, int x, int y);

/**
 * Updates a ball's velocity based on a constant deceleration
 *
 * @param ball The ball to update
 */
void updateBallPosition(Ball* ball);

/**
 * Draws the ball
 *
 * @param ball The ball to update
 */
void renderBall(Ball* ball);

#endif // POOL_BALL_INCLUDE
