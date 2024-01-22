#pragma once

#include "entity.h"
#include "entity_manager.h"

#include <SFML/Graphics.hpp>

struct PlayerConfig {float P_SHAPE_RAD, P_COLLISION_RAD; int P_F_COLOR_R, P_F_COLOR_G, P_F_COLOR_B, P_O_COLOR_R, P_O_COLOR_G, P_O_COLOR_B, P_SHAPE_VERT; float P_SPEED, P_O_THICKNESS;};
struct EnemyConfig {float E_SHAPE_RAD, E_COLLISION_RAD; int E_O_COLOR_R, E_O_COLOR_G, E_O_COLOR_B, E_MIN_VERTICES, E_MAX_VERTICES, E_SMALL_LIFE, E_SPAWN_INTVL; float E_MIN_SPEED, E_MAX_SPEED, E_O_THICKNESS;};
struct BulletConfig {float B_SHAPE_RAD, B_COLLISION_RAD; int B_F_COLOR_R, B_F_COLOR_G, B_F_COLOR_B, B_O_COLOR_R, B_O_COLOR_G, B_O_COLOR_B, B_SHAPE_VERT, B_LIFE; float B_SPEED, B_O_THICKNESS;};

class Game
{
  sf::RenderWindow m_window;
  EntityManager    m_entities;
  sf::Font         m_font;
  sf::Text         m_text;
  PlayerConfig     m_playerConfig;
  EnemyConfig      m_enemyConfig;
  BulletConfig     m_bulletConfig;
  unsigned int     m_score = 0;
  unsigned int     m_currentFrame = 0;
  unsigned int     m_lastEnemySpawnTime = 0;
  bool             m_paused = false;
  bool             m_running = true;

  Entity* m_player;

  void init     (const std::string&);

  void sMovement      ();
  void sUserInput     ();
  void sLifespan      ();
  void sRender        ();
  void sEnemySpawner  ();
  void sCollision     ();

  void spawnPlayer       ();
  void spawnEnemy        ();
  void spawnSmallEnemies (Entity* entity);
  void spawnBullet       (Entity* entity, const Vec2& mousePos);
  void spawnSpecialWeapon(Entity* entity);
  void lockOnTarget      (Entity* entity);

public:
  explicit Game(const std::string&);
  void     run();
};