#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector> // Для vector
#include <memory> // Для shared_ptr
#include <iostream> // Для cout, cerr
#include <utility>

#include "entity.hpp"
#include "entity_vector.hpp" 
#include "wallet.hpp"

class Client : public Entity {
protected:
    string name;
    Entityvector wallets; // Это объект Entityvector
public:
    Client(string id, string name);
    virtual ~Client();
    void addWallet(shared_ptr<Wallet> wallet);
    double getTotalBalance() const;
    virtual double calculateCommission(double amount) const = 0;
    virtual double getMaxTransactionLimit() const = 0;
    
    // Этот метод уже существует и возвращает const vector<shared_ptr<Entity>>&
    const vector<shared_ptr<Entity>>& getWallets() const;

    const Entityvector& getWalletsObject() const { return wallets; }

    string getId() const override;
    string getName() const;
};

// Standart client
class StandardClient : public Client{
    public:
        StandardClient(string id, string name);
        double calculateCommission(double amount) const override;
        double getMaxTransactionLimit()const override;
        string getBenefits() const;
        ~StandardClient()override{}
};

// Golden client
class GoldClient : public Client{
    public:
        GoldClient(string id, string name);
        double calculateCommission(double amount) const override;
        double getMaxTransactionLimit()const override;
        string getBenefits() const;
        ~GoldClient()override{}
};

// Platinum client
class PlatinumClient : public Client{
    public:
        PlatinumClient(string id, string name);
        double calculateCommission(double amount) const override;
        double getMaxTransactionLimit()const override;
        string getBenefits() const;
        ~PlatinumClient()override{}
};

class ClientNode {
    public:
        shared_ptr<Client> data;
        ClientNode* left;
        ClientNode* right;
    
        ClientNode(shared_ptr<Client> data);
        ~ClientNode();
};

#endif
