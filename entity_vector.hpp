#ifndef ENTITY_VECTOR_HPP
#define ENTITY_VECTOR_HPP

#include <vector>
#include <string>
#include <memory> // For shared_ptr
#include <iostream> // For cout, cerr

#include "entity.hpp"
using namespace std;

class Entityvector {
private:
    vector<shared_ptr<Entity>> entities;
public:
    Entityvector() = default;
    ~Entityvector() = default;

    void addEntity(shared_ptr<Entity> entity);
    bool removeEntity(const string& id);
    shared_ptr<Entity> getEntity(const string& id) const;
    const vector<shared_ptr<Entity>>& getAllEntities() const;
};

#endif
