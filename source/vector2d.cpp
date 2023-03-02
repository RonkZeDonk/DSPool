#include "vector2d.hpp"

Vector2D::Vector2D(int x, int y) {
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::operator+(Vector2D& other) {
    return Vector2D(this->x + other.x, this->y + other.y);
}
void Vector2D::operator+=(Vector2D& other) {
    this->x += other.x;
    this->y += other.y;
}

Vector2D Vector2D::operator-(Vector2D& other) {
    return Vector2D(this->x - other.x, this->y - other.y);
}
void Vector2D::operator-=(Vector2D& other) {
    this->x -= other.x;
    this->y -= other.y;
}

Vector2D Vector2D::operator*(int factor) {
    return Vector2D(mulf32(this->x, factor), mulf32(this->y, factor));
}
void Vector2D::operator*=(int factor) {
    this->x *= factor;
    this->y *= factor;
}

Vector2D Vector2D::operator/(int factor) {
    assert(factor != 0);
    return Vector2D(divf32(this->x, factor), divf32(this->y, factor));
}
void Vector2D::operator/=(int factor) {
    assert(factor != 0);
    this->x /= factor;
    this->y /= factor;
}

int32 Vector2D::length() {
    return sqrtf32(mulf32(this->x, this->x) + mulf32(this->y, this->y));
}

int32 vectorDotProduct(Vector2D* a, Vector2D* b) {
    return mulf32(a->x, b->x) + mulf32(a->y, b->y);
}

int32 Vector2D::dot(Vector2D other) {
    return vectorDotProduct(this, &other);
}
