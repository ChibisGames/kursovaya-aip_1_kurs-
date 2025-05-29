#include <iostream>
#include "wallet.hpp"
#include <string> 

using namespace std;

Wallet::Wallet(string id, string ownerId, double balance) : Entity(id), balance(balance), ownerId(ownerId) {}

void Wallet::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    } else {
        cerr << "Warning: Attempted to deposit a non-positive amount." << endl;
    }
}

bool Wallet::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    } else {
        cerr << "Error: Cannot withdraw " << amount << ". Current balance: " << balance << endl;
    }
    return false;
}

double Wallet::getBalance() const {
    return balance;
}

string Wallet::getId() const {
    return id;
}

string Wallet::getOwnerId() const {
    return ownerId;
}
