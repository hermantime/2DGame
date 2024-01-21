#include "game.h"
//#include "/Users/herman.genis/CLionProjects/assignment2/math.h"

#include <cassert>
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
  m_bulletConfig.B_O_THICKNESS   = std::stof(x.at(46));
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
  if (m_player->cInput->up)
  {
    m_player->cTransform->pos.y -= m_player->cTransform->velocity.y;
  }
  if (m_player->cInput->down)
  {
    m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
  }
  if (m_player->cInput->left)
  {
    m_player->cTransform->pos.x -= m_player->cTransform->velocity.x;
  }
  if (m_player->cInput->right)
  {
    m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
  }
  for (Entity* e : m_entities.getEntities())
  {
    if (e->type != Entity::E_PLAYER)
    {
      e->cTransform->pos += e->cTransform->velocity;
    }
  }
}

void Game::sUserInput()
{
  sf::Event event;
  while (m_window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      m_running = false;
    }

    if (event.type == sf::Event::KeyPressed)
    {
      switch (event.key.code)
      {
        case sf::Keyboard::P:
          m_paused = !m_paused;
          break;
        case sf::Keyboard::W:
          m_player->cInput->up = true;
          break;
        case sf::Keyboard::A:
          m_player->cInput->left = true;
          break;
        case sf::Keyboard::S:
          m_player->cInput->down = true;
          break;
        case sf::Keyboard::D:
          m_player->cInput->right = true;
          break;
        case sf::Keyboard::E: // special ability
          spawnSpecialWeapon(m_player);
          break;
        default:
          break;
      }
    }

    if (event.type == sf::Event::KeyReleased)
    {
      switch (event.key.code)
      {
        case sf::Keyboard::W:
          m_player->cInput->up = false;
          break;
        case sf::Keyboard::A:
          m_player->cInput->left = false;
          break;
        case sf::Keyboard::S:
          m_player->cInput->down = false;
          break;
        case sf::Keyboard::D:
          m_player->cInput->right = false;
          break;
        case sf::Keyboard::E: // special ability
          spawnSpecialWeapon(m_player);
          break;
        case sf::Keyboard::Escape: // quit game
          m_running = false;
          break;
        default:
          break;
      }
    }

    if (event.type == sf::Event::MouseButtonPressed && !m_paused)
    {
      switch (event.mouseButton.button)
      {
        case sf::Mouse::Left:
          spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
          break;
      }
    }
  }
}

void Game::sLifespan()
{
  for (Entity*& e : m_entities.getEntities())
  {
    if (e->type != Entity::E_PLAYER)
    {
      e->cLifespan->remaining_frames--;
      if (e->cLifespan->remaining_frames == 0)
        e->destroy();
    }
  }
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
  if (m_currentFrame % m_enemyConfig.E_SPAWN_INTVL == 0)
    spawnEnemy();
}

void Game::sBorderCollision()
{
  for (Entity*& entity : m_entities.getEntities())
  {
    if (!entity->isActive())
    {
      continue;
    }
    Vec2* ePos = &entity->cTransform->pos;
    float rad = entity->cShape->circle.getRadius();
    for (Entity*& entity2 : m_entities.getEntities())
    {
      Vec2* e2Pos = &entity2->cTransform->pos;
      float e2Rad = entity2->cShape->circle.getRadius();
      if (entity->type == Entity::E_BULLET && entity2->type == Entity::E_ENEMY)
      {
        if (ePos->dist(*e2Pos) < (rad+e2Rad)*(rad+e2Rad))
        {
          entity->destroy();
          entity2->destroy();
        }
      }
      else if (entity->type == Entity::E_PLAYER && entity2->type == Entity::E_ENEMY)
      {
        if (ePos->dist(*e2Pos) < (rad+e2Rad)*(rad+e2Rad))
        {
          std::cout << "Reset impl\n";
        }
      }
      else if (entity->type == Entity::E_ENEMY && entity2->type == Entity::E_ENEMY && entity != entity2)
      {
        if (ePos->dist(*e2Pos) < (rad+e2Rad)*(rad+e2Rad))
        {
          Vec2 nVec = Vec2(ePos->x-e2Pos->x, ePos->y-e2Pos->y);
          nVec.normalize();
          Vec2 tVec = Vec2(-nVec.y, nVec.x); // perp to normal vec
          float dotNorm1 = nVec.x * entity->cTransform->velocity.x + nVec.y * entity->cTransform->velocity.y;
          float dotTan1  = tVec.x * entity->cTransform->velocity.x + tVec.y * entity->cTransform->velocity.y;
          float dotNorm2 = nVec.x * entity2->cTransform->velocity.x + nVec.y * entity2->cTransform->velocity.y;
          float dotTan2  = tVec.x * entity2->cTransform->velocity.x + tVec.y * entity2->cTransform->velocity.y;
          float p1 = (dotNorm1 * (rad - e2Rad) + 2.0f * e2Rad * dotNorm2) / (rad + e2Rad);
          float p2 = (dotNorm2 * (e2Rad - rad) + 2.0f * rad * dotNorm1) / (rad + e2Rad);
          entity->cTransform->velocity.x = tVec.x * dotTan1 + nVec.x * p1;
          entity->cTransform->velocity.y = tVec.y * dotTan1 + nVec.y * p1;
          entity2->cTransform->velocity.x = tVec.x * dotTan2 + nVec.x * p2;
          entity2->cTransform->velocity.y = tVec.y * dotTan2 + nVec.y * p2;
        }
      }
    }
    switch (entity->type)
    {
      case Entity::E_BULLET: {
        if (ePos->x < 0 || ePos->x > m_window.getSize().x || ePos->y < 0 || ePos->y > m_window.getSize().y) {
          entity->destroy();
        }
        break;
      }
      case Entity::E_ENEMY: { // treating everything as circle, add shape functionality later
        if (ePos->x < rad)
        {
          std::cout << "Enemy wall collision\n";
          entity->cTransform->pos.x = rad;
          entity->cTransform->velocity.x *= -1;
        }
        else if (ePos->x > m_window.getSize().x-rad)
        {
          std::cout << "Enemy wall collision\n";
          entity->cTransform->pos.x = m_window.getSize().x-rad;
          entity->cTransform->velocity.x *= -1;
        }
        if (ePos->y < rad)
        {
          std::cout << "Enemy wall collision\n";
          entity->cTransform->pos.y = rad;
          entity->cTransform->velocity.y *= -1;
        }
        else if (ePos->y > m_window.getSize().y-rad)
        {
          std::cout << "Enemy wall collision\n";
          entity->cTransform->pos.y = m_window.getSize().y-rad;
          entity->cTransform->velocity.y *= -1;
        }
        break;
      }
      case Entity::E_PLAYER: {
        if (ePos->x < -rad)
        {
          std::cout << "Travel-through: px - border\n";
          entity->cTransform->pos.x = m_window.getSize().x + rad - entity->cShape->circle.getOutlineThickness();
        }
        else if (ePos->x > m_window.getSize().x+rad)
        {
          std::cout << "Travel-through: px - border\n";
          entity->cTransform->pos.x = -rad + entity->cShape->circle.getOutlineThickness();
        }
        if (ePos->y < -rad)
        {
          std::cout << "Travel-through: py - border\n";
          entity->cTransform->pos.y = m_window.getSize().y + rad - entity->cShape->circle.getOutlineThickness();
        }
        else if (ePos->y > m_window.getSize().y+rad)
        {
          std::cout << "Travel-through: py - border\n";
          entity->cTransform->pos.y = -rad + entity->cShape->circle.getOutlineThickness();
        }
        break;
      }
    }
  }
}

void Game::spawnPlayer()
{
  Entity* player = m_entities.addEntity(Entity::E_PLAYER);
  Vec2 pos = Vec2(static_cast<float>(m_window.getSize().x)/2, static_cast<float>(m_window.getSize().y)/2);
  player->cTransform = new CTransform(pos, Vec2(m_playerConfig.P_SPEED, m_playerConfig.P_SPEED), 0.0);
  player->cShape = new CShape(m_playerConfig.P_SHAPE_RAD, m_playerConfig.P_SHAPE_VERT, sf::Color(m_playerConfig.P_F_COLOR_R, m_playerConfig.P_F_COLOR_G, m_playerConfig.P_F_COLOR_B), sf::Color(m_playerConfig.P_O_COLOR_R, m_playerConfig.P_O_COLOR_G, m_playerConfig.P_O_COLOR_B), m_playerConfig.P_O_THICKNESS);
  player->cShape->circle.setOrigin(m_playerConfig.P_SHAPE_RAD, m_playerConfig.P_SHAPE_RAD);
  player->cCollision = new CCollision(m_playerConfig.P_COLLISION_RAD);
  player->cInput = new CInput();
  m_player = player;
}

void Game::spawnEnemy() // direction, normalize, scale, add
{
  // spawn enemy with config variables, within bounds of window
  Entity* enemy = m_entities.addEntity(Entity::E_ENEMY);
  auto r = [](int l, int u) { return rand() % (u-l)+l; };
  float rad = m_enemyConfig.E_SHAPE_RAD;
  Vec2 pos(r(rad, m_window.getSize().x-rad), r(rad, m_window.getSize().y-rad));
  Vec2 vel(r(m_enemyConfig.E_MIN_SPEED, m_enemyConfig.E_MAX_SPEED), r(m_enemyConfig.E_MIN_SPEED, m_enemyConfig.E_MAX_SPEED));
  float angle = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2.0f * M_PI;
  vel.x = std::cos(angle) * r(2,7);
  vel.y = std::sin(angle) * r(2,7);
  enemy->cTransform = new CTransform(pos, vel, r(0, m_enemyConfig.E_MAX_VERTICES));
  enemy->cShape = new CShape(m_enemyConfig.E_SHAPE_RAD, r(m_enemyConfig.E_MIN_VERTICES, m_enemyConfig.E_MAX_VERTICES), sf::Color(m_enemyConfig.E_O_COLOR_R, m_enemyConfig.E_O_COLOR_G, m_enemyConfig.E_O_COLOR_B), sf::Color(m_enemyConfig.E_O_COLOR_R, m_enemyConfig.E_O_COLOR_G, m_enemyConfig.E_O_COLOR_B), m_enemyConfig.E_O_THICKNESS);
  enemy->cShape->circle.setOrigin(m_enemyConfig.E_SHAPE_RAD, m_enemyConfig.E_SHAPE_RAD);
  enemy->cCollision = new CCollision(m_enemyConfig.E_COLLISION_RAD);
  enemy->cScore = new CScore(r(100, m_enemyConfig.E_MAX_VERTICES * 200));
  enemy->cLifespan = new CLifespan(r(m_enemyConfig.E_SMALL_LIFE, m_enemyConfig.E_SMALL_LIFE * 10));
  m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(Entity* entity) // when enemy die spawn this
{

}

void Game::spawnBullet(Entity* entity, const Vec2& target)
{
  Entity* bullet = m_entities.addEntity(Entity::E_BULLET);
  Vec2 entityPos = Vec2(entity->cShape->circle.getPosition().x, entity->cShape->circle.getPosition().y);
  Vec2 bulletSpawn = target - entityPos;
  bulletSpawn.normalize();
  bulletSpawn.scale(entity->cShape->circle.getRadius());
  bulletSpawn += entityPos;
  Vec2 bulletVel = target - bulletSpawn;
  bulletVel.normalize();
  bulletVel.scale(m_bulletConfig.B_SPEED);
  bullet->cTransform = new CTransform(bulletSpawn, bulletVel, 0);
  bullet->cShape     = new CShape(m_bulletConfig.B_SHAPE_RAD, m_bulletConfig.B_SHAPE_VERT, sf::Color(m_bulletConfig.B_F_COLOR_R, m_bulletConfig.B_F_COLOR_G, m_bulletConfig.B_F_COLOR_B), sf::Color(m_bulletConfig.B_O_COLOR_R, m_bulletConfig.B_O_COLOR_G, m_bulletConfig.B_O_COLOR_B), m_bulletConfig.B_O_THICKNESS);
  bullet->cShape->circle.setOrigin(m_bulletConfig.B_SHAPE_RAD, m_bulletConfig.B_SHAPE_RAD);
  bullet->cCollision = new CCollision(m_bulletConfig.B_COLLISION_RAD);
  bullet->cLifespan  = new CLifespan(m_bulletConfig.B_LIFE);
}

void Game::spawnSpecialWeapon(Entity* entity)
{

}

void Game::run()
{
  while (m_running) // add pause functionality in here, ends game
  {
    m_entities.update();
    sRender();
    sUserInput();
    if (!m_paused)
    {
      sEnemySpawner();
      sBorderCollision();
      sMovement();
      sLifespan();
      m_currentFrame++; // move when implement 'pause'
    }
  }
  m_entities.cleanEntities();
}
