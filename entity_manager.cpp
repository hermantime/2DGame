#include "entity_manager.h"

Entity *EntityManager::addEntity(Entity::Type tag)
{
  Entity* entity = new Entity(m_totalEntities++, tag);
  m_toAdd.push_back(entity);
  return entity;
}

void EntityManager::update()
{
  for (Entity*& e : m_toAdd)
  {
    m_entities.push_back(e);
  }
  m_toAdd.clear();

  for (int i = 0; i < m_entities.size(); ++i)
    if (!m_entities[i]->m_active)
    {
      delete m_entities[i];
      m_entities.erase(m_entities.begin()+i);
    }
}

EntityVec& EntityManager::getEntities() { return m_entities; }
EntityVec EntityManager::getEntities(Entity::Type e_type)
{
  EntityVec filtered {};
  std::copy_if(m_entities.begin(), m_entities.end(), std::back_inserter(filtered), [&e_type](const Entity* e) {
    return e->type == e_type;
  });
  return filtered;
}
void EntityManager::cleanEntities()
{
  for (auto& e : m_entities)
    delete e;
}