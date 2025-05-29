#include "entity_vector.hpp"
#include "entity.hpp"
#include <iostream>
#include <algorithm> // For remove_if

using namespace std; // Added for the requested removal of std::

void Entityvector::addEntity(shared_ptr<Entity> entity) {
    if (!entity) {
        cerr << "Attempted to add nullptr shared_ptr<Entity>\n";
        return;
    }
    cout << "Adding entity: " << entity->getId() << endl;
    entities.push_back(entity);
    cout << "Entities size now: " << entities.size() << endl;
}

bool Entityvector::removeEntity(const string& id) {
    auto initial_size = entities.size();
    entities.erase(remove_if(entities.begin(), entities.end(),
                                   [&](const shared_ptr<Entity>& entity) {
                                       return entity && entity->getId() == id;
                                   }),
                   entities.end());
    return entities.size() < initial_size;
}

shared_ptr<Entity> Entityvector::getEntity(const string& id) const {
    for (const auto& entity : entities) {
        if (entity && entity->getId() == id) {
            return entity;
        }
    }
    return nullptr;
}

const vector<shared_ptr<Entity>>& Entityvector::getAllEntities() const {
    return entities;
}
