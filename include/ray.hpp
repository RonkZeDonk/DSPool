#include "vector2d.hpp"
#include "table.hpp"

class Ray {
    public:
        int angle;
        Vector2D position;
        Vector2D directionVector;

        Ray(Vector2D position, int angle);
        Ray() {};

        ~Ray() {};

        // Shoots ray out in the direction of `angle` from `position`
        // Returns the where the ray hits a ball
        Vector2D shootRay(Ball balls[16]);
};
