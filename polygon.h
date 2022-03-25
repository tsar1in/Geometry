#include <iostream>
#include <cmath>
#include <vector>
#pragma once
namespace geometry {
struct Polygon : public IShape {
  std::vector<Point> a;
  Polygon(const std::vector<Point>& other) {  // NOLINT
    for (auto& i : other) {
      a.push_back(i);
    }
  }
  Polygon& Move(const Vector& other) override;
  bool ContainsPoint(const Point& other) const override;
  bool CrossesSegment(const Segment& other) const override;
  Polygon* Clone() const override;
  std::string ToString() const override;
};

}  // namespace geometry
