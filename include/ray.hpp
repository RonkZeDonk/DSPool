#include "vec2.hpp"
#include "ball.hpp"

class Ray {
    public:
        int angle;
        Vec2 position;
        Vec2 directionVector;

        Ray(Vec2 position, int angle);
        Ray() {};

        ~Ray() {};

        // Shoots ray out in the direction of `angle` from `position`
        // Returns the where the ray hits a ball
        Vec2 shootRay(Ball balls[16]);
};
