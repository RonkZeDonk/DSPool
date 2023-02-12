#include "ray.hpp"
#include "ball.hpp"

Ray::Ray(Vector2D position, int angle) {
    this->position = position;
    this->angle = angle;
}

Vector2D Ray::shootRay(Ball balls[16]) {
    // From table.cpp updateTablePosition COLLIDE_DISTANCE
    // TODO this constant doesn't exist in the other file yet
    int COLLIDE_DISTANCE = 49000 / 2;
    Vector2D hitpos = this->position;
    this->directionVector = Vector2D(
        cosLerp(this->angle),
        sinLerp(this->angle)
    );

    // Not including the white ball (the ray is coming from there most
    // of the time).
    while (
        hitpos.x > inttof32(15) && hitpos.x < inttof32(230) &&
        hitpos.y > inttof32(16) && hitpos.y < inttof32(166)
        ) {
        for (int i = 0; i < 15; i++) {
            Vector2D* vec = &balls[i].position;
            // if hitpos is within `radius` of the ball then resolve hit
            if (hitpos.minus(*vec).length() <= COLLIDE_DISTANCE) {
                return hitpos;
            }
        }
        hitpos = hitpos.plus(this->directionVector);
    }
    return hitpos;
}
