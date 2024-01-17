//
// Created by Herman Genis on 1/4/24.
//

#include "math.h"
#include "vec2.h"

Vec2::Vec2() : x(1.0), y(1.0) {}

Vec2::Vec2(const float& xin, const float& yin) : x(xin), y(yin) {}

// Consider using fabs(x-y) < EPSILON
bool Vec2::operator == (const Vec2& other) const
{
  return other.x == x && other.y == y;
}

bool Vec2::operator != (const Vec2& other) const
{
  return other.x != x || other.y != y;
}

Vec2 Vec2::operator + (const Vec2& other) const
{
  return Vec2(other.x + x, other.y + x);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
  return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const Vec2& other) const
{
  return Vec2(other.x * x, other.y * y);
}

Vec2 Vec2::operator / (const Vec2& rhs) const
{
  return Vec2(x / rhs.x, y / rhs.y);
}

void Vec2::operator += (const Vec2& rhs)
{
  x += rhs.x;
  y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
}

void Vec2::operator *= (const Vec2& rhs)
{
  x *= rhs.x;
  y *= rhs.y;
}

void Vec2::operator /= (const Vec2& rhs)
{
  x /= rhs.x;
  y /= rhs.y;
}

float Vec2::dist(const Vec2& other) const
{
  return sqrt(pow(other.x - x) + pow(other.y - y));
}

float Vec2::length() const
{
  return sqrt(x * x + y * y);
}
