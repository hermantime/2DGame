#pragma once

#include "components.h"
#include <string>
#include <iostream>

class Entity {
public:
  enum Type {E_BULLET, E_ENEMY, E_PLAYER} type;

private:

  friend class EntityManager;

  bool        m_active = true;
  size_t      m_id = 0;

  Entity(size_t id, Entity::Type tag) : m_id(id), type(tag) {}
  ~Entity() {
    std::cout << "Bullet destroy\n";
    delete cTransform;
    delete cShape;
    delete cCollision;
    delete cInput;
    delete cScore;
    delete cLifespan;
  }

public:
  CTransform * cTransform = nullptr;
  CShape     * cShape     = nullptr;
  CCollision * cCollision = nullptr;
  CInput     * cInput     = nullptr;
  CScore     * cScore     = nullptr;
  CLifespan  * cLifespan  = nullptr;

  [[nodiscard]] bool               isActive() const { return m_active; }
  [[nodiscard]] size_t             id() const { return m_id; }
  [[nodiscard]] Type               who() const { return type; }
  void                             destroy() { m_active = false; }
};