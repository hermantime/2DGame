//
// Created by Herman Genis on 1/4/24.
//

#pragma once

class Vec2 
{
public:
  float x;
  float y;

  Vec2();
  Vec2(const float&, const float&);

  bool operator == (const Vec2&) const;
  bool operator != (const Vec2&) const;

  Vec2 operator + (const Vec2&) const;
  Vec2 operator - (const Vec2&) const;
  Vec2 operator * (const Vec2&) const;
  Vec2 operator / (const Vec2&) const;

  void operator += (const Vec2&);
  void operator -= (const Vec2&);
  void operator *= (const Vec2&);
  void operator /= (const Vec2&);

  [[nodiscard]] float dist  (const Vec2&) const;
  [[nodiscard]] float sdist (const Vec2&) const;
  [[nodiscard]] float length()            const;

  void normalize();
  void scale    (float);
  void abs      ();
};
