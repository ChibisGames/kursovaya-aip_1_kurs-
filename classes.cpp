#include <iostream>
#include <vector>
#include <string>

#include "classes.h"

using namespace std;


Entity::~Entity() {}
string Entity::getId() const {return id;}


//TODO all methods
EntityVector::EntityVector() {}
EntityVector::~EntityVector() {}
void EntityVector::addEntity(Entity* entity) {entities.push_back(entity);}
bool EntityVector::removeEntity(string id) {}
Entity* EntityVector::getEntity(string id) {}
vector<Entity*>& EntityVector::getAllEntities() {}


double GoldClient::calculateCommission(double amount) const {return amount * 0.01;}
double GoldClient::getMaxTransactionLimit() const {return 10000;}
string GoldClient::getBenefits() const
{ 
    return "Priority processing, low commissions"; 
}

double PlatinumClient::calculateCommission(double amount) const {return amount * 0.02;}
double PlatinumClient::getMaxTransactionLimit() const {return 5000;}
string PlatinumClient::getBenefits() const
{ 
    return "Bonus rewards, moderate commissions";
}

double StandardClient::calculateCommission(double amount) const {return amount * 0.05;}
double StandardClient::getMaxTransactionLimit() const {return 1000;}
string StandardClient::getBenefits() const
{ 
    return "Standard access";
}

