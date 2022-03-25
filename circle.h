#include <iostream>
#include <cmath>
#include <vector>
#pragma once
namespace geometry {
struct Circle : public IShape {
  Point a;
  int64_t R;
  Circle() : a(Point(0, 0)), R(0) {
  }
  Circle(const Point& x1, int64_t l) : a(x1), R(l) {
  }
  Circle& Move(const Vector& other) override;
  bool ContainsPoint(const Point& other) const override;
  bool CrossesSegment(const Segment& other) const override;
  Circle* Clone() const override;
  std::string ToString() const override;
};

}  // namespace geometry
