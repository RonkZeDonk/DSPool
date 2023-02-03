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

        // TODO(commit): doc comments
        Vector2D plus(Vector2D other);
        Vector2D minus(Vector2D other);
        Vector2D multiply(int factor);
        Vector2D divide(int factor);

        int32 length();
        int32 dot(Vector2D other);
};

// TODO(commit): doc comments
Vector2D vectorAdd(Vector2D* a, Vector2D* b);
Vector2D vectorSubtract(Vector2D* a, Vector2D* b);
Vector2D vectorScalarMultiply(Vector2D* vector, int factor);
Vector2D vectorScalarDivide(Vector2D* vector, int factor);

int32 vectorLength(Vector2D* vector);
int32 vectorDotProduct(Vector2D* a, Vector2D* b);

#endif // VECTOR2D_INCLUDE
