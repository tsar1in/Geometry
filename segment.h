#include <iostream>
#include <cmath>
#include <vector>
#pragma once
namespace geometry {
struct Segment : public IShape {
  Point a;
  Point b;
  Segment() = default;
  Segment(const Point& x1, const Point& x2) : a(x1), b(x2) {
  }
  Segment(const Segment& other) : a(other.a), b(other.b) {
  }
  Segment& operator=(const Segment& other) {
    a = other.a;
    b = other.b;
    return *this;
  }
  Segment& Move(const Vector& other) override;
  bool ContainsPoint(const Point& other) const override;
  bool CrossesSegment(const Segment& other) const override;
  Segment* Clone() const override;
  std::string ToString() const override;
};

}  // namespace geometry
