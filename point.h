#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#pragma once
namespace geometry {
struct Point : public IShape {
  int64_t x;
  int64_t y;
  Point() : x(0), y(0) {
  }
  Point(int64_t a, int64_t b) : x(a), y(b) {
  }
  Point(const Point& other) : x(other.x), y(other.y) {
  }
  Point& operator=(const Point& other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  Point& Move(const Vector&) override;
  bool ContainsPoint(const Point& other) const override;
  bool CrossesSegment(const Segment& other) const override;
  Point* Clone() const override;
  std::string ToString() const override;
  friend Vector operator-(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
  }
};

}  // namespace geometry
