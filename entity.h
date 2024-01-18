//
// Created by Herman Genis on 1/4/24.
//

#pragma once

#include "components.h"
#include <string>
#include <iostream>

class Entity {

  friend class EntityManager;

  enum {E_BULLET, E_ENEMY, E_PLAYER} type;
  bool        m_active = true;
  size_t      m_id = 0;
  std::string m_tag = "default";

  Entity(size_t id, const std::string& tag) : m_id(id), m_tag(tag)
  {
    switch (tag[0])
    {
      case 'b':
        type = Entity::E_BULLET;
        break;
      case 'e':
        type = Entity::E_ENEMY;
        break;
      case 'p':
        type = Entity::E_PLAYER;
        break;
    }
  }
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
  [[nodiscard]] const std::string& tag() const { return m_tag; }
  [[nodiscard]] size_t             id() const { return m_id; }
  void                             destroy() { m_active = false; }
};