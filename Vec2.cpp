#include "Vec2.h"

Vec2 Vec2::operator+(const Vec2& other) const {
	return Vec2(x + other.x, y + other.y);
}

Vec2& Vec2::operator+=(const Vec2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vec2 Vec2::operator-(const Vec2& other) const {
	return Vec2(x - other.x, y - other.y);
}

Vec2& Vec2::operator-=(const Vec2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vec2 Vec2::operator*(const float other) const {
	return Vec2(x * other, y * other);
}

//Vec2 Vec2::operator*(const Vec2& other) const {
//	return Vec2(x * other.x, y * other.y);
//}

Vec2& Vec2::operator*=(const float other) {
	x *= other;
	y *= other;
	return *this;
}

Vec2 Vec2::operator/(const float other) const {
	return Vec2(x / other, y /other);
}

Vec2& Vec2::operator/=(const float other) {
	x /= other;
	y /= other;
	return *this;
}

float Vec2::magSquared() const {
	return (x * x) + (y * y);
}

float Vec2::magnitude() const {
	return std::sqrtf(magSquared());
}

void Vec2::normalize() {
	float mag_sq = magSquared();
	if (mag_sq > 0.f) {//can remove 0 check if dont need later
		float inv_mag = 1.0f / std::sqrtf(mag_sq);
		x *= inv_mag;
		y *= inv_mag;
	}
}

Vec2 Vec2::normalized() const {
	Vec2 copy = *this;
	copy.normalize();
	return copy;
}

double Vec2::angleTo(const Vec2& other) const {// Returns angle in radians (should return float maybe?)
	return std::atan2(other.y - y, other.x - x);
}

Vec2 Vec2::directionTo(const Vec2& other) const {
	return (other - *this).normalized();
}

float Vec2::distanceTo(const Vec2& other) const {
	return (other - *this).magnitude();
}

float Vec2::distanceSqTo(const Vec2& other) const {
	return (other - *this).magSquared();
}

Vec2 Vec2::distanceTo_V(const Vec2& other) const {
	return other - *this;
}
