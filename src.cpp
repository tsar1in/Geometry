#include <iostream>
#include <cmath>
#include <vector>
#include "../vector.h"
#include "../point.h"
#include "../segment.h"
#include "../ray.h"
#include "../line.h"
#include "../circle.h"
#include "../polygon.h"
using namespace geometry;
int64_t Scalar(const Vector& a1, const Vector& a2);
int64_t Vec(const Vector& a1, const Vector& a2);
bool IfOnRay(Point a3, Point a1, Point a2);
bool IfOnSegment(const Point& a3, const Point& a2, const Point& a1);
bool IfIntersect(const Segment& first, const Segment& second);
bool InSide(const std::vector<Point>& a, const Point& c, size_t n);
long double DistanceToSegment(const Point& x1, const Point& x2, const Point& x3);
Point& Point::Move(const Vector& other) {
  x += other.x;
  y += other.y;
  return *this;
}
bool Point::ContainsPoint(const Point& other) const {
  return (x == other.x && y == other.y);
}
Point* Point::Clone() const {
  return (new Point(x, y));
}
std::string Point::ToString() const {
  std::string ans;
  std::stringstream ss;
  ss << "Point(" << x << ", " << y << ")";
  ans = ss.str();
  return ans;
}
inline Segment& Segment::Move(const Vector& other) {
  a.Move(other);
  b.Move(other);
  return *this;
}
inline bool Segment::ContainsPoint(const Point& other) const {
  return (other.CrossesSegment(*this));
}
inline bool Segment::CrossesSegment(const Segment& other) const {
  return (IfIntersect(*this, other));
}
inline Segment* Segment::Clone() const {
  return (new Segment(a, b));
}
inline std::string Segment::ToString() const {
  std::string ans;
  std::stringstream ss;
  ss << "Segment(Point(" << a.x << ", " << a.y << "), Point(" << b.x << ", " << b.y << "))";
  ans = ss.str();
  return ans;
}
inline Line& Line::Move(const Vector& other) {
  a.Move(other);
  b.Move(other);
  return *this;
}
inline bool Line::ContainsPoint(const Point& other) const {
  int64_t al = a.y - b.y;
  int64_t bl = b.x - a.x;
  int64_t cl = a.x * b.y - b.x * a.y;
  return (al * other.x + bl * other.y + cl == 0);
}
inline bool Line::CrossesSegment(const Segment& other) const {
  Vector nap(a, b);
  Vector one(a, other.a);
  Vector two(a, other.b);
  if (Vec(nap, one) * Vec(nap, two) <= 0) {
    return true;
  }
  return false;
}
inline Line* Line::Clone() const {
  return (new Line(a, b));
}
inline std::string Line::ToString() const {
  std::string ans;
  std::stringstream ss;
  ss << "Line(" << b.y - a.y << ", " << a.x - b.x << ", " << b.x * a.y - a.x * b.y << ")";
  ans = ss.str();
  return ans;
}
inline Ray& Ray::Move(const Vector& other) {
  a.Move(other);
  b.Move(other);
  return *this;
}
inline bool Ray::ContainsPoint(const Point& other) const {
  Vector tmp1(b.x - a.x, b.y - a.y);
  Vector tmp2(other.x - a.x, other.y - a.y);
  return (Vec(tmp1, tmp2) == 0 && Scalar(tmp1, tmp2) >= 0);
}
inline bool Ray::CrossesSegment(const Segment& other) const {
  Vector nap(a, b);
  Vector one(a, other.a);
  Vector two(a, other.b);
  if (IfOnRay(other.a, a, b) || IfOnRay(other.b, a, b)) {
    return true;
  }
  if (Vec(nap, one) * Vec(nap, two) <= 0) {
    if (Vec(one, two) >= 0) {
      return true;
    }
  }
  return false;
}
inline Ray* Ray::Clone() const {
  return (new Ray(a, b));
}
inline std::string Ray::ToString() const {
  std::string ans;
  std::stringstream ss;
  ss << "Ray(Point(" << a.x << ", " << a.y << "), Vector(" << b.x - a.x << ", " << b.y - a.y << "))";
  ans = ss.str();
  return ans;
}
inline Circle& Circle::Move(const Vector& other) {
  a.Move(other);
  return *this;
}
inline bool Circle::ContainsPoint(const Point& other) const {
  Vector tmp(a, other);
  return (tmp.Length() <= R);
}
inline bool Circle::CrossesSegment(const Segment& other) const {
  Vector tmp1(a, other.a);
  Vector tmp2(a, other.b);
  if (tmp1.Length() < R && tmp2.Length() < R) {
    return false;
  }
  long double r = DistanceToSegment(other.a, other.b, a);
  if (r <= R) {
    return true;
  }
  return false;
}
inline Circle* Circle::Clone() const {
  return (new Circle(a, R));
}
inline std::string Circle::ToString() const {
  std::string ans;
  std::stringstream ss;
  ss << "Circle(Point(" << a.x << ", " << a.y << "), " << R << ")";
  ans = ss.str();
  return ans;
}
inline Polygon& Polygon::Move(const Vector& other) {
  for (size_t i = 0; i < a.size(); i++) {
    a[i].Move(other);
  }
  return *this;
}
inline bool Polygon::ContainsPoint(const Point& other) const {
  return InSide(a, other, a.size());
}
inline bool Polygon::CrossesSegment(const Segment& other) const {
  for (size_t i = 0; i < a.size() - 1; i++) {
    if (IfIntersect(other, Segment(a[i], a[i + 1]))) {
      return true;
    }
  }
  return (IfIntersect(other, Segment(a[a.size() - 1], a[0])));
}
inline Polygon* Polygon::Clone() const {
  return (new Polygon(a));
}
inline std::string Polygon::ToString() const {
  std::string ans;
  std::stringstream ss;
  ss << "Polygon(";
  for (size_t i = 0; i < a.size() - 1; i++) {
    ss << "Point(" << a[i].x << ", " << a[i].y << "), ";
  }
  ss << "Point(" << a[a.size() - 1].x << ", " << a[a.size() - 1].y << "))";
  ans = ss.str();
  return ans;
}
inline int64_t Scalar(const Vector& a1, const Vector& a2) {
  return (a1.x * a2.x + a1.y * a2.y);
}
inline int64_t Vec(const Vector& a1, const Vector& a2) {
  return (a1.x * a2.y - a1.y * a2.x);
}
inline bool IfOnRay(Point a3, Point a1, Point a2) {
  Vector tmp1(a2.x - a1.x, a2.y - a1.y);
  Vector tmp2(a3.x - a1.x, a3.y - a1.y);
  return (Vec(tmp1, tmp2) == 0 && Scalar(tmp1, tmp2) >= 0);
}
inline bool IfOnSegment(const Point& a3, const Point& a2, const Point& a1) {
  return (IfOnRay(a3, a1, a2) && IfOnRay(a3, a2, a1));
}
inline bool IfIntersect(const Segment& first, const Segment& second) {
  int64_t one = ((first.a.y - first.b.y) * second.a.x + (first.b.x - first.a.x) * second.a.y + first.a.x * first.b.y -
                 first.b.x * first.a.y);
  int64_t two = (first.a.y - first.b.y) * second.b.x + (first.b.x - first.a.x) * second.b.y + first.a.x * first.b.y -
                first.b.x * first.a.y;
  int64_t three = (second.a.y - second.b.y) * first.a.x + (second.b.x - second.a.x) * first.a.y +
                  second.a.x * second.b.y - second.b.x * second.a.y;
  int64_t four = (second.a.y - second.b.y) * first.b.x + (second.b.x - second.a.x) * first.b.y +
                 second.a.x * second.b.y - second.b.x * second.a.y;
  int64_t maxax = Max(first.a.x, first.b.x);
  int64_t minax = Min(first.a.x, first.b.x);
  int64_t maxay = Max(first.a.y, first.b.y);
  int64_t minay = Min(first.a.y, first.b.y);
  bool t1 = (minax <= second.a.x && second.a.x <= maxax) || (minax <= second.b.x && second.b.x <= maxax);
  bool t2 = (minay <= second.a.y && second.a.y <= maxay) || (minay <= second.b.y && second.b.y <= maxay);
  int64_t maxbx = Max(second.a.x, second.b.x);
  int64_t minbx = Min(second.a.x, second.b.x);
  int64_t maxby = Max(second.a.y, second.b.y);
  int64_t minby = Min(second.a.y, second.b.y);
  bool t3 = (minbx <= first.a.x && first.a.x <= maxbx) || (minbx <= first.b.x && first.b.x <= maxbx);
  bool t4 = (minby <= first.a.y && first.a.y <= maxby) || (minby <= first.b.y && first.b.y <= maxby);
  if (one * two <= 0 && three * four <= 0) {
    if ((t1 || t3) && (t2 || t4)) {
      return true;
    }
  }
  return false;
}
inline bool InSide(const std::vector<Point>& a, const Point& c, size_t n) {
  int64_t s = 0;
  Point x(c.x + 10000, c.y + 1);
  Segment ans(c, x);
  for (size_t i = 0; i < n - 1; i++) {
    s += IfIntersect(ans, Segment(a[i], a[i + 1]));
  }
  s += IfIntersect(ans, Segment(a[n - 1], a[0]));
  for (size_t i = 0; i < n - 1; i++) {
    if (IfOnSegment(c, a[i], a[i + 1])) {
      return true;
    }
  }
  if (IfOnSegment(c, a[n - 1], a[0])) {
    return true;
  }
  for (size_t i = 0; i < n; i++) {
    if (c.x == a[i].x && c.y == a[i].y) {
      return true;
    }
  }
  return (s % 2 != 0);
}
inline Vector::Vector(const Point& an, const Point& bn) {
  x = bn.x - an.x;
  y = bn.y - an.y;
}
inline bool Point::CrossesSegment(const Segment& other) const {
  if (other.a.x == other.b.x && other.a.y == other.b.y) {
    if (x == other.a.x && y == other.a.y) {
      return true;
    }
    return false;
  }
  return IfOnSegment(*this, other.a, other.b);
}
long double DistanceToSegment(const Point& x1, const Point& x2, const Point& x3) {
  Vector a(x1, x2);
  Vector b(x2, x1);
  Vector ac(x1, x3);
  Vector bc(x2, x3);
  if (Scalar(a, ac) > 0 && Scalar(b, bc) > 0) {
    return std::abs(Vec(ac, a) / a.Length());
  }
  if (Scalar(a, ac) <= 0) {
    return ac.Length();
  }
  if (Scalar(b, bc) <= 0) {
    return bc.Length();
  }
  return 0.0;
}
