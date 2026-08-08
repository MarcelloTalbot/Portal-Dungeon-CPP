#pragma once

#include <cmath>
#include <concepts>

struct Vec2 {
	float x, y;

	constexpr Vec2(float x = {}, float y = {}) : x(x), y(y) {}

	Vec2 operator+(const Vec2& other) const;
	Vec2& operator+=(const Vec2& other);

	Vec2 operator-(const Vec2& other) const;
	Vec2& operator-=(const Vec2& other);

	Vec2 operator*(const float other) const;
	Vec2& operator*=(const float other);

	Vec2 operator/(const float other) const;
	Vec2& operator/=(const float other);

	[[nodiscard]] float magSquared() const;
	[[nodiscard]] float magnitude() const;

	void normalize();
	[[nodiscard]] Vec2 normalized() const;

	[[nodiscard]] double angleTo(const Vec2& other) const;
	[[nodiscard]] Vec2 directionTo(const Vec2& other) const;
	[[nodiscard]] float distanceTo(const Vec2& other) const;
	[[nodiscard]] float distanceSqTo(const Vec2& other) const;
	[[nodiscard]] Vec2 distanceTo_V(const Vec2& other) const; // Same as other - this
};

inline Vec2 operator*(const float scalar, const Vec2& vector) {
	return vector * scalar;
}

//template<std::floating_point F>
//struct Vec {
//	F x, y;
//
//	constexpr Vec(F x = {}, F y = {}) : x(x), y(y) {}
//
//	Vec operator+(const Vec& other) const {
//		return Vec(x + other.x, y + other.y);
//	}
//	Vec& operator+=(const Vec& other) {
//		x += other.x;
//		y += other.y;
//		return *this;
//	}
//
//	Vec operator-(const Vec& other) const {
//		return Vec(x - other.x, y - other.y);
//	}
//	Vec& operator-=(const Vec& other) {
//		x -= other.x;
//		y -= other.y;
//		return *this;
//	}
//
//	Vec operator*(const F other) const {//could add template for other types
//		return Vec(x * other, y * other);
//	}
//	Vec& operator*=(const F other) {
//		x *= other;
//		y *= other;
//		return *this;
//	}
//
//	Vec operator/(const F other) const {
//		return Vec(x / other, y / other);
//	}
//	Vec& operator/=(const F other) {
//		x /= other;
//		y /= other;
//		return *this;
//	}
//
//	[[nodiscard]] F magSquared() const {
//		return (x * x) + (y * y);
//	}
//	[[nodiscard]] F magnitude() const {
//		return std::sqrt(magSquared());
//	}
//
//	void normalize() {
//		F mag_sq = magSquared();
//		if (mag_sq > F{}) {//can remove 0 check if dont need later
//			F inv_mag = static_cast<F>(1) / std::sqrt(mag_sq);
//			x *= inv_mag;
//			y *= inv_mag;
//		}
//	}
//	[[nodiscard]] Vec normalized() const {
//		Vec copy = *this;
//		copy.normalize();
//		return copy;
//	}
//
//	[[nodiscard]] double angleTo(const Vec& other) const { // Returns angle in radians.
//		return std::atan2(other.y - y, other.x - x);
//	}
//	[[nodiscard]] Vec directionTo(const Vec& other) const {
//		return (other - *this).normalized();
//	}
//	[[nodiscard]] F distanceTo(const Vec& other) const {
//		return (other - *this).magnitude();
//	}
//};
//
//template<std::floating_point F>
//inline Vec<F> operator*(const F scalar, const Vec<F>& vector) {
//	return vector * scalar;
//}