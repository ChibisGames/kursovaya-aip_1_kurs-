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



Transaction::Transaction(string id, string senderWalletId, string recipientWalletId, double amount, TxType type, double commission):
    Entity(id) {this->senderWalletId; this->recipientWalletId=recipientWalletId; 
        this->amount = amount, this->type = type; this->commission = commission;}
Transaction::~Transaction() {}
string Transaction::getId() const {return id;}
string Transaction::getDetails() const {} //TODO: хз, что здесь надо сделать


TransactionNode::TransactionNode(Transaction* data) 
{this->data = data; this->prev = nullptr; this->next = nullptr;}
TransactionNode::~TransactionNode() {delete data;}
Transaction* TransactionNode::getData() const {return data;}
void TransactionNode::setPrevious(TransactionNode *prev) {this->prev = prev;}
TransactionNode* TransactionNode::getPrevious() {return this->prev;}
void TransactionNode::setNext(TransactionNode *next) {this->next = next;}
TransactionNode* TransactionNode::getNext() {return this->next;}


TransactionList::TransactionList() {head = nullptr; tail = nullptr; size = 0;}
TransactionList::~TransactionList() 
{
    TransactionNode* current = head;
    for (int i = 0; i < size; i++)
    {
        TransactionNode* next = current->next;
        delete current;
        current = next;
    }
}
void TransactionList::addTransaction(Transaction* tx) 
{
    TransactionNode* newNode = new TransactionNode(tx);
    if (!head) {head = tail = newNode;} 
    else 
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}
bool TransactionList::removeTransaction(string id) 
{
    TransactionNode* current = head;
    for (int i = 0; i < size; i++)
    {
        if (current->data->getId() == id) 
        {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;
            delete current;
            size--;
            return true;
        }
        current = current->next;
    }
    return false;
}
Transaction* TransactionList::getTransaction(string id) 
{
    TransactionNode* current = head;
    for (int i = 0; i < size; i++)
    {
        if (current->getData()->getId() == id) return current->data;
        current = current->next;
    }
    return nullptr;
}
void TransactionList::displayTransactions() 
{
    TransactionNode* current = head;
    for (int i = 0; i < size; i++)
    {
        current->data->getDetails();
        current = current->next;
    }
}


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

