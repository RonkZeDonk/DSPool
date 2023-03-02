#ifndef VECTOR2D_INCLUDE
#define VECTOR2D_INCLUDE

#include <nds.h>

class Vector2D {
    public:
        // Represented as a 20.12 fixed point number
        int32 x;
        // Represented as a 20.12 fixed point number
        int32 y;

        /**
         * Create a 2d vector
        */
        Vector2D(int x, int y);
        Vector2D() {};

        // TODO: destructor
        ~Vector2D() {};

        Vector2D operator+(Vector2D& other);
        void operator+=(Vector2D& other);
        Vector2D operator-(Vector2D& other);
        void operator-=(Vector2D& other);
        Vector2D operator*(int factor);
        void operator*=(int factor);
        Vector2D operator/(int factor);
        void operator/=(int factor);

        int32 length();
        int32 dot(Vector2D other);
};

int32 vectorDotProduct(Vector2D* a, Vector2D* b);

#endif // VECTOR2D_INCLUDE
