//
// Created by Herman Genis on 1/4/24.
//

#pragma once

#include "components.h"
#include <string>

class Entity {

  friend class EntityManager;

  bool        m_active = true;
  size_t      m_id = 0;
  std::string m_tag = "default";

  Entity(size_t id, const std::string& tag) : m_id(id), m_tag(tag) {}
  ~Entity() {
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