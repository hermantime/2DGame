//
// Created by Herman Genis on 1/4/24.
//

#include "entity_manager.h"

Entity *EntityManager::addEntity(const std::string& tag)
{
  Entity* entity = new Entity(m_totalEntities++, tag);
  m_toAdd.push_back(entity);
  return entity;
}

void EntityManager::update() // called at each frame by engine
{
  for (Entity* e : m_toAdd)
  {
    m_entities.push_back(e);
    m_entityMap[e->m_tag].push_back(e);
  }
  m_toAdd.clear();
  auto erase = [](EntityVec& v) {v.erase(std::remove_if(v.begin(), v.end(),
                                  [](Entity*& e) {
                                          if (!e->m_active) {
                                            delete e;
                                            e = nullptr;
                                            return true;
                                          }
                                          return false; }),
                                         v.end());};
  erase(m_entities);
  for (auto& pair : m_entityMap)
    erase(pair.second);
}

EntityVec& EntityManager::getEntities() { return m_entities; }
EntityVec& EntityManager::getEntities(const std::string & tag) { return m_entityMap[tag]; }

void EntityManager::cleanEntities()
{
  for (auto& e : m_entities)
    delete e;
}