#include <iostream>
#include <vector>
#include <string>

#include "classes.h"

using namespace std;


Entity::Entity(const string id) {this->id = id;}
Entity::~Entity() {}
string Entity::getId() const {return id;}


EntityVector::EntityVector() {vector<Entity*> entities;}
EntityVector::~EntityVector() {entities.clear();}
void EntityVector::addEntity(Entity* entity) {entities.push_back(entity);}
bool EntityVector::removeEntity(const string& id) 
{
    for (auto cursor = entities.cbegin(); cursor != entities.cend(); cursor++) 
    {
        if ((*cursor)->getId() == id) 
        {
            entities.erase(cursor);
            cout << "Entity removed!" << endl;
            return true;
        }
    }
    cout << "There is no such entity!" << endl;
    return false;
}
Entity* EntityVector::getEntity(const string& id) const
{
    for (const auto& entity : entities) 
    {
        if (entity->getId() == id) {return entity;}
    }
    return nullptr;
}
vector<Entity*>& EntityVector::getAllEntities() {return entities;}


Wallet::Wallet(string id, string ownerId, double balance) : 
    Entity(id) {this->ownerId = ownerId, this->balance = balance;}
void Wallet::deposit(double amount) {balance += amount;}
bool Wallet::withdraw(double amount) 
{
    if (balance >= amount)
    {
        balance -= amount;
        cout << "Withdraw success" << endl;
        return true;
    }
    cout << "Withdraw NOT success" << endl;
    return false;
}
double Wallet::getBalance() const {return balance;}
string Wallet::getId() const {return id;}


Client::Client(string id, string name) : Entity(id) {this->name = name;}
Client::~Client() {wallets.~EntityVector();}
void Client::addWallet(Wallet* wallet) {wallets.addEntity(wallet);}
double Client::getTotalBalance() 
{
    double total = 0;
    for (auto wallet : wallets.getAllEntities())
    {
        total += dynamic_cast<Wallet*>(wallet)->getBalance();
    }
    return total;
}
double Client::calculateCommission(double amount) {}
double Client::getMaxTransactionLimit() const {}
string Client::getId() const {return id;}



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

