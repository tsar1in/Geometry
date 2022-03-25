#include <iostream>
#include <cmath>
#include <vector>
#pragma once
// Коэфы выходят с *(-1) и функция пересечения с отрезком
// A(a.y - b.y), B(b.x - a.x), C(a.x * b.y - b.x * a.y)
namespace geometry {
struct Line : public IShape {
  Point a;
  Point b;
  Line() = default;
  Line(const Line& other) : a(other.a), b(other.b) {
  }
  Line(const Point& x1, const Point& x2) : a(x1), b(x2) {
  }
  Line& Move(const Vector& other) override;
  bool ContainsPoint(const Point& other) const override;
  bool CrossesSegment(const Segment& other) const override;
  Line* Clone() const override;
  std::string ToString() const override;
};

}  // namespace geometry
