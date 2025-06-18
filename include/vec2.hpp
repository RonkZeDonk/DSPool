#ifndef VEC2_INCLUDE
#define VEC2_INCLUDE

#include <nds.h>

class Vec2 {
    public:
        // Represented as a 20.12 fixed point number
        int32 x;
        // Represented as a 20.12 fixed point number
        int32 y;

        /**
         * Create a 2d vector
        */
        Vec2(int x, int y);
        Vec2() {};

        // TODO: destructor
        ~Vec2() {};

        Vec2 operator+(Vec2* other);
        Vec2 operator+(Vec2 other);
        void operator+=(Vec2* other);
        void operator+=(Vec2 other);

        Vec2 operator-(Vec2* other);
        Vec2 operator-(Vec2 other);
        void operator-=(Vec2* other);
        void operator-=(Vec2 other);

        Vec2 operator*(int factor);
        void operator*=(int factor);

        Vec2 operator/(int factor);
        void operator/=(int factor);

        int32 squareLength();
        int32 length();
        Vec2 normalize();
        int32 dot(Vec2 other);
};

#endif // VEC2_INCLUDE
