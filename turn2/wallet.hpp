#ifndef WALLET_H
#define WALLET_H
#include <string>
#include "entity.hpp"
using namespace std;

class Wallet : public Entity {
private:
    double balance;
    string ownerId;
public:
    Wallet(string id, string ownerId, double balance);
    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;
    string getId() const override;
    string getOwnerId() const;
    ~Wallet() override {}
};

#endif
