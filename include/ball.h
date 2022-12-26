#ifndef POOL_BALL_INCLUDE
#define POOL_BALL_INCLUDE

#include <nds.h>
#include <gl2d.h>
#include <stdio.h>

/**
 * Possible teams for pool balls
 */
typedef enum {
    TeamA,
    TeamB,

    BlackBall
} Team;

/**
 * Pool ball struct
 */
typedef struct {
    // Ball's team
    Team team;

    // The ball's graphics
    glImage sprite[1];

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
 * @param team Ball team
 * @param gfx_mem Pointer to the ball's graphics memory
 * @param x x-position of the ball
 * @param y y-position of the ball
 *
 * @returns A constructed Ball
 */
Ball initBall(int id, Team team, glImage sprite[1], int x, int y);

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
