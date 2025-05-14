#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class TxType { TRANSFER };

class Entity
{
    string id;

public:
    virtual ~Entity();
    virtual string getId() const; 
};

class EntityVector
{
    vector<Entity*> entities;
public:
    EntityVector();
    ~EntityVector();
    void addEntity(Entity* entity);
    bool removeEntity(const string& id);
    Entity* getEntity(const string& id);
    vector<Entity*>& getAllEntities();
};

class Client : public Entity
{
    string name;
    EntityVector wallets;
public:
    Client(string id, string name);
    virtual ~Client();
    void addWallet(Wallet* wallet);
    double getTotalNalance();
    virtual double calculateCommission(double amount);
    virtual double getMaxTransactionLimit();
    string getId();
};

class GoldClient : public Client 
{
public:
    GoldClient(const string id, const string name); 
    double calculateCommission(double amount) const;
    double getMaxTransactionLimit() const;
    string getBenefits() const;
};
    
class PlatinumClient : public Client 
{
public:
    PlatinumClient(const string id, const string name);
    double calculateCommission(double amount) const;
    double getMaxTransactionLimit() const;
    string getBenefits() const;
};
    
class StandardClient : public Client 
{
public:
    StandardClient(const string id, const string name);
    double calculateCommission(double amount) const;
    double getMaxTransactionLimit() const;
    string getBenefits() const;
};

class Wallet : public Entity
{
    double balance;
    string ownerId;
public:
    Wallet(string id, string ownerId, double balance);
    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance();
    string getId();
};

class Transaction : Entity
{
    string senderWalletId;
    string recipientWalletId;
    double amount;
    TxType type;
    double commission;
public:
    Transaction(string id, string senderWalletId, string recipientWalletId, double amount, TxType type, double commission);
    string getId();
    string getDetails();
};

class TransactionNode
{
    Transaction* data;
    TransactionNode* prev;
    TransactionNode* next;
public:
    TransactionNode(Transaction* data);
    ~TransactionNode();
};

class TransactionList 
{
    TransactionNode* head;
    TransactionNode* tail;
    int size;
public:
    TransactionList();
    ~TransactionList();
    void addTransaction(Transaction* tx);
    bool removeTransaction(string id);
    Transaction* getTransaction(string id);
    void displayTransactions();
};

class ClientNode 
{
    Client* data;
    ClientNode* left;
    ClientNode* right;
public:   
    ClientNode(Client* data);
    ~ClientNode();
};
    
class ClientBST 
{
    ClientNode* root;
public:
    ClientBST();
    ~ClientBST();
    void insert(Client* client);
    bool remove(string id);
    Client* find(const string& id);
    void displayInOrder();
};
    
class Blockchain 
{
    ClientBST clients;
    TransactionList transactions;
public:
    Blockchain();
    ~Blockchain();    
    void addClient(Client* client);
    bool processTransaction(Transaction* tx);
    void displayClients();
    void displayTransactions();
    bool saveData();
};
