

#include "game.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <iostream>

 Game::Game(const std::string& config)
{
  init(config);
}

void Game::init(const std::string& config)
{
  std::vector<std::string> x;
  std::ifstream file(config);
  std::string s{};
  char c;
  while (file.get(c))
  {
    if (c == ' ' || c == '\n')
    {
      x.push_back(s);
      s = "";
      continue;
    }
    s += c;
  }
  int WINDOW_WIDTH    = std::stoi(x.at(1));
  int WINDOW_HEIGHT   = std::stoi(x.at(2));
  unsigned int FPS    = std::stoi(x.at(3));
  auto FULLSCREEN  = std::stoi(x.at(4)) ? sf::Style::Fullscreen : sf::Style::Default;
  
  m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");
  m_window.setFramerateLimit(FPS);

  std::string FONT    = x.at(6);
  int FONT_SIZE       = std::stoi(x.at(7));
  int FONT_R          = std::stoi(x.at(8));
  int FONT_G          = std::stoi(x.at(9));
  int FONT_B          = std::stoi(x.at(10));
  
  m_playerConfig.P_SHAPE_RAD     = std::stof(x.at(12));
  m_playerConfig.P_COLLISION_RAD = std::stof(x.at(13));
  m_playerConfig.P_SPEED       = std::stof(x.at(14));
  m_playerConfig.P_F_COLOR_R     = std::stoi(x.at(15));
  m_playerConfig.P_F_COLOR_G     = std::stoi(x.at(16));
  m_playerConfig.P_F_COLOR_B     = std::stoi(x.at(17));
  m_playerConfig.P_O_COLOR_R     = std::stoi(x.at(18));
  m_playerConfig.P_O_COLOR_G     = std::stoi(x.at(19));
  m_playerConfig.P_O_COLOR_B     = std::stoi(x.at(20));
  m_playerConfig.P_O_THICKNESS   = std::stof(x.at(21));
  m_playerConfig.P_SHAPE_VERT    = std::stoi(x.at(22));
  m_enemyConfig.E_SHAPE_RAD     = std::stof(x.at(24));
  m_enemyConfig.E_COLLISION_RAD = std::stof(x.at(25));
  m_enemyConfig.E_MIN_SPEED   = std::stof(x.at(26));
  m_enemyConfig.E_MAX_SPEED   = std::stof(x.at(27));
  m_enemyConfig.E_O_COLOR_R     = std::stoi(x.at(28));
  m_enemyConfig.E_O_COLOR_G     = std::stoi(x.at(29));
  m_enemyConfig.E_O_COLOR_B     = std::stoi(x.at(30));
  m_enemyConfig.E_O_THICKNESS   = std::stof(x.at(31));
  m_enemyConfig.E_MIN_VERTICES  = std::stoi(x.at(32));
  m_enemyConfig.E_MAX_VERTICES  = std::stoi(x.at(33));
  m_enemyConfig.E_SMALL_LIFE    = std::stoi(x.at(34));
  m_enemyConfig.E_SPAWN_INTVL   = std::stoi(x.at(35));
  m_bulletConfig.B_SHAPE_RAD     = std::stof(x.at(37));
  m_bulletConfig.B_COLLISION_RAD = std::stof(x.at(38));
  m_bulletConfig.B_SPEED       = std::stof(x.at(39));
  m_bulletConfig.B_F_COLOR_R     = std::stoi(x.at(40));
  m_bulletConfig.B_F_COLOR_G     = std::stoi(x.at(41));
  m_bulletConfig.B_F_COLOR_B     = std::stoi(x.at(42));
  m_bulletConfig.B_O_COLOR_R     = std::stoi(x.at(43));
  m_bulletConfig.B_O_COLOR_G     = std::stoi(x.at(44));
  m_bulletConfig.B_O_COLOR_B     = std::stoi(x.at(45));
  m_bulletConfig.B_O_THICKNESS   = std::stoi(x.at(46));
  m_bulletConfig.B_SHAPE_VERT    = std::stoi(x.at(47));
  m_bulletConfig.B_LIFE          = std::stoi(x.at(48));

  spawnPlayer(); // guaranteed to be the first in the entity array
}

void Game::setPaused(bool paused)
{
  m_paused = paused; // m_paused = m_paused ? false : true; + remove arg
}

void Game::sMovement()
{

}

void Game::sUserInput()
{

}

void Game::sLifespan()
{

}

void Game::sRender()
{
  m_window.clear();
  EntityVec* es = &m_entities.getEntities();
  for (Entity* e : *es)
  {
    e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
    e->cTransform->angle += 1.0f;
    e->cShape->circle.setRotation(e->cTransform->angle);
    m_window.draw(e->cShape->circle);
  }
  m_window.display();
}

void Game::sEnemySpawner()
{
  spawnEnemy();
}

void Game::sEnemyCollision()
{

}

void Game::sCollision()
{

}

void Game::spawnPlayer()
{
  std::cout << "Spawning player\n";
  Entity* player = m_entities.addEntity("player");
  player->cTransform = new CTransform(Vec2(static_cast<float>(m_window.getSize().x)/2, static_cast<float>(m_window.getSize().y)/2), Vec2(m_playerConfig.P_SPEED, m_playerConfig.P_SPEED), 0.0);
  player->cShape = new CShape(m_playerConfig.P_SHAPE_RAD, m_playerConfig.P_SHAPE_VERT, sf::Color(m_playerConfig.P_F_COLOR_R, m_playerConfig.P_F_COLOR_G, m_playerConfig.P_F_COLOR_B), sf::Color(m_playerConfig.P_O_COLOR_R, m_playerConfig.P_O_COLOR_G, m_playerConfig.P_O_COLOR_B), m_playerConfig.P_O_THICKNESS);
  player->cCollision = new CCollision(m_playerConfig.P_COLLISION_RAD);
  player->cInput = new CInput();
  m_player = player;
}

void Game::spawnEnemy()
{
  std::cout << "Spawning enemy\n";
  // spawn enemy with config variables, within bounds of window
  Entity* enemy = m_entities.addEntity("enemy");
  auto r = [](int l, int u) { return rand() % (u-l)+u; };
  enemy->cTransform = new CTransform(Vec2(r(0,m_window.getSize().x), r(0,m_window.getSize().y)),
                                     Vec2(r(m_enemyConfig.E_MIN_SPEED, m_enemyConfig.E_MAX_SPEED), r(m_enemyConfig.E_MIN_SPEED, m_enemyConfig.E_MAX_SPEED)),
                                     r(0, m_enemyConfig.E_MAX_VERTICES));
  enemy->cShape = new CShape(m_enemyConfig.E_SHAPE_RAD, r(m_enemyConfig.E_MIN_VERTICES, m_enemyConfig.E_MAX_VERTICES), sf::Color(m_enemyConfig.E_O_COLOR_R, m_enemyConfig.E_O_COLOR_G, m_enemyConfig.E_O_COLOR_B), sf::Color(m_enemyConfig.E_O_COLOR_R, m_enemyConfig.E_O_COLOR_G, m_enemyConfig.E_O_COLOR_B), m_enemyConfig.E_O_THICKNESS);
  enemy->cCollision = new CCollision(m_enemyConfig.E_COLLISION_RAD);
  enemy->cScore = new CScore(r(100, m_enemyConfig.E_MAX_VERTICES * 200));
  enemy->cLifespan = new CLifespan(r(m_enemyConfig.E_SMALL_LIFE, m_enemyConfig.E_SMALL_LIFE * 60));
  m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(Entity* entity)
{

}

void Game::spawnBullet(Entity* entity, const Vec2& bullets)
{
  Entity* bullet = m_entities.addEntity("bullet");
}

void Game::spawnSpecialWeapon(Entity* entity)
{

}

void Game::run()
{
  while (m_running) // add pause functionality in here, ends game
  {
    m_entities.update();
    if (!m_paused)
    {
      sEnemySpawner();
      sMovement();
      sCollision();
      sUserInput();
      m_currentFrame++; // move when implement 'pause'
    }
    sRender(); // still works, nothing else does, shapes move
  }
}
