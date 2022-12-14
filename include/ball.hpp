#ifndef POOL_BALL_INCLUDE
#define POOL_BALL_INCLUDE

#include <nds.h>
#include <gl2d.h>
#include <stdio.h>

/**
 * Possible teams for pool balls
 */
enum Team {
    TeamA,
    TeamB,

    BlackBall,
    CueBall,
};

class Ball {
    public:
        // Ball's team
        Team team;

        // The ball's graphics
        glImage sprite[1];

        // Ball x position. Represented as a 20.12 fixed point number.
        int32 xPos;
        // Ball y position. Represented as a 20.12 fixed point number.
        int32 yPos;

        // Ball x velocity. Represented as a 20.12 fixed point number.
        int32 xVel;
        // Ball y velocity. Represented as a 20.12 fixed point number.
        int32 yVel;

        // ---- FUNCTIONS ----

        /**
         * Initalize pool ball
         *
         * @param team Ball team
         * @param sprite Pointer to the ball's graphics memory
         * @param xPos x-position of the ball
         * @param yPos y-position of the ball
         */
        Ball(Team team, glImage sprite[1], int xPos, int yPos);
        Ball() {}; // default ctor

        // TODO: Destructor
        ~Ball() {};

        /**
         * Updates a ball's velocity based on a constant deceleration
         */
        void updateBallPosition();

        /**
         * Draws the ball
         */
        void renderBall();
};

#endif // POOL_BALL_INCLUDE
