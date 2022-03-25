#include <iostream>
#include <cmath>
#include <vector>
#pragma once
//Проблемы с выводом и функция пересечения отрезка
namespace geometry {
struct Ray : public IShape {
  Point a;
  Point b;
  Ray() = default;
  Ray(const Point& x1, const Point& x2) : a(x1), b(x2) {
  }
  Ray(const Ray& other) : a(other.a), b(other.b) {
  }
  Ray& Move(const Vector& other) override;
  bool ContainsPoint(const Point& other) const override;
  bool CrossesSegment(const Segment& other) const override;
  Ray* Clone() const override;
  std::string ToString() const override;
};

}  // namespace geometry
