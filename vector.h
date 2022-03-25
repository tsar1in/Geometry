#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#pragma once
namespace geometry {
struct IShape;
struct Vector;
struct Point;
struct Segment;
struct Line;
struct Ray;
struct Polygon;
struct Circle;
inline int64_t Max(int64_t a, int64_t b) {
  if (a > b) {
    return a;
  }
  return b;
}
inline int64_t Min(int64_t a, int64_t b) {
  if (a < b) {
    return a;
  }
  return b;
}
struct Vector {
  int64_t x;
  int64_t y;
  Vector() = default;
  Vector(const Vector& other) = default;
  Vector(int64_t a, int64_t b) : x(a), y(b) {
  }
  Vector(const Point& an, const Point& bn);
  Vector& operator=(const Vector& other) = default;
  long double Length() const {
    return sqrt(static_cast<double>(x) * static_cast<double>(x) + static_cast<double>(y) * static_cast<double>(y));
  }
  Vector operator-() const {
    return {-x, -y};
  }
  Vector operator+() const {
    return *this;
  }
  friend Vector operator*(Vector& other, int n) {
    return {n * other.x, n * other.y};
  }
  friend Vector operator/(Vector& other, int n) {
    return {other.x / n, other.y / n};
  }
  Vector& operator*=(int n) {
    x *= n;
    y *= n;
    return *this;
  }
  Vector& operator/=(int n) {
    x /= n;
    y /= n;
    return *this;
  }
  friend bool operator==(const Vector& a, const Vector& b) {
    return (a.x == b.x && a.y == b.y);
  }
};
struct IShape {
  virtual IShape& Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual bool CrossesSegment(const Segment&) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() const = 0;
  virtual ~IShape() = default;
};

}  // namespace geometry
