#include "vec2.hpp"

Vec2::Vec2(int x, int y) {
    this->x = x;
    this->y = y;
}

Vec2 Vec2::operator+(Vec2* other) {
    return Vec2(this->x + other->x, this->y + other->y);
}
Vec2 Vec2::operator+(Vec2 other) {
    return Vec2(this->x + other.x, this->y + other.y);
}
void Vec2::operator+=(Vec2* other) {
    this->x += other->x;
    this->y += other->y;
}
void Vec2::operator+=(Vec2 other) {
    this->x += other.x;
    this->y += other.y;
}

Vec2 Vec2::operator-(Vec2* other) {
    return Vec2(this->x - other->x, this->y - other->y);
}
Vec2 Vec2::operator-(Vec2 other) {
    return Vec2(this->x - other.x, this->y - other.y);
}
void Vec2::operator-=(Vec2* other) {
    this->x -= other->x;
    this->y -= other->y;
}
void Vec2::operator-=(Vec2 other) {
    this->x -= other.x;
    this->y -= other.y;
}

Vec2 Vec2::operator*(int factor) {
    return Vec2(mulf32(this->x, factor), mulf32(this->y, factor));
}
void Vec2::operator*=(int factor) {
    this->x *= factor;
    this->y *= factor;
}

Vec2 Vec2::operator/(int factor) {
    assert(factor != 0);
    return Vec2(divf32(this->x, factor), divf32(this->y, factor));
}
void Vec2::operator/=(int factor) {
    assert(factor != 0);
    this->x /= factor;
    this->y /= factor;
}

int32 Vec2::squareLength() {
    return mulf32(this->x, this->x) + mulf32(this->y, this->y);
}
int32 Vec2::length() {
    return sqrtf32(squareLength());
}
Vec2 Vec2::normalize() {
    int32 magnitude = this->length();
    return Vec2(divf32(this->x, magnitude), divf32(this->y, magnitude));
}

int32 Vec2::dot(Vec2 other) {
    return mulf32(this->x, other.x) + mulf32(this->y, other.y);
}
