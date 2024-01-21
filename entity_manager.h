#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "entity.h"

typedef std::vector<Entity*> EntityVec;
class EntityManager
{
  EntityVec m_toAdd {};
  EntityVec m_entities {};
  size_t m_totalEntities = 0;

public:
  EntityManager() = default;
  Entity*    addEntity(Entity::Type);

  EntityVec& getEntities  ();
  EntityVec  getEntities  (Entity::Type);
  void       update       ();
  void       cleanEntities();
};