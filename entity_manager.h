#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "entity.h"

typedef std::vector<Entity*> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;
class EntityManager
{
  EntityVec m_toAdd {};
  EntityVec m_entities {};
  EntityMap m_entityMap {};
  size_t m_totalEntities = 0;

public:
  EntityManager() = default;
  Entity* addEntity(const std::string&);

  EntityVec& getEntities  ();
  EntityVec& getEntities  (const std::string&);
  void       update       ();
  void       cleanEntities();
};