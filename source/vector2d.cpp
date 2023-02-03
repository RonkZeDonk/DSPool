#include "vector2d.hpp"

Vector2D::Vector2D(int x, int y) {
    this->x = x;
    this->y = y;
}

Vector2D vectorAdd(Vector2D* a, Vector2D* b) {
    return Vector2D(a->x + b->x, a->y + b->y);
}

Vector2D Vector2D::plus(Vector2D other) {
    return vectorAdd(this, &other);
}

Vector2D vectorSubtract(Vector2D* a, Vector2D* b) {
    return Vector2D(a->x - b->x, a->y - b->y);
}

Vector2D Vector2D::minus(Vector2D other) {
    return vectorSubtract(this, &other);
}

Vector2D vectorScalarMultiply(Vector2D* vector, int factor) {
    return Vector2D(mulf32(vector->x, factor), mulf32(vector->y, factor));
}

Vector2D Vector2D::multiply(int factor) {
    return vectorScalarMultiply(this, factor);
}

Vector2D vectorScalarDivide(Vector2D* vector, int factor) {
    assert(factor != 0);
    return Vector2D(divf32(vector->x, factor), divf32(vector->y, factor));
}

Vector2D Vector2D::divide(int factor) {
    return vectorScalarDivide(this, factor);
}

int32 vectorLength(Vector2D* vector) {
    return sqrtf32(mulf32(vector->x, vector->x) + mulf32(vector->y, vector->y));
}

int32 Vector2D::length() {
    return vectorLength(this);
}

int32 vectorDotProduct(Vector2D* a, Vector2D* b) {
    return mulf32(a->x, b->x) + mulf32(a->y, b->y);
}

int32 Vector2D::dot(Vector2D other) {
    return vectorDotProduct(this, &other);
}
