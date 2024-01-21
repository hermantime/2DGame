#pragma once

#include <SFML/Graphics.hpp>
#include "vec2.h"

class CTransform // x:y position, x:y velocity, turning angle
{ // where an entity is, its speed, angle of rotation
public:
  Vec2 pos;
  Vec2 velocity;
  float angle;

  CTransform(const Vec2& p, const Vec2& vel, float a) : pos(p), velocity(vel), angle(a) {}
  ~CTransform() = default;
};

class CShape
{
public:
  sf::CircleShape circle;

  CShape(float rad, int vertices, const sf::Color& fill, const sf::Color& outline, float thickness)
    : circle(rad, vertices)
  {
    circle.setFillColor(fill);
    circle.setOutlineColor(outline);
    circle.setOutlineThickness(thickness);
    circle.setOrigin(rad, rad);
  }
  ~CShape() = default;
};

class CCollision // collision radius of the shape
{
public:
  float radius;
  explicit CCollision(float rad) : radius(rad) {}
  ~CCollision() = default;
};

class CScore // number of sides * 100 (large) or number of sides * 200 (small)
{
public:
  int score;
  explicit CScore(int s) : score(s) {}
  ~CScore() = default;
};

class CLifespan
{
public:
  int remaining_frames; // amount of lifespan remaining on entity
  int total_frames;     // the total initial amount of lifespan

  explicit CLifespan(int frameCount) :remaining_frames(frameCount), total_frames(frameCount) {}
  ~CLifespan() = default;
};

class CInput // tracks whether we are pressing keys / if object has this - it is controllable by us
{
public:
  bool up    {};
  bool left  {};
  bool right {};
  bool down  {};
  bool shoot {};

  CInput() = default;
  ~CInput() = default;
};