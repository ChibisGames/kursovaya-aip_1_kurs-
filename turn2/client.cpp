#include "client.hpp"
#include "wallet.hpp"
//#include "standard_client.hpp"
//#include "gold_client.hpp"
//#include "platinum_client.hpp"
#include <string>
#include <iostream>
#include <memory> // For dynamic_pointer_cast

using namespace std;

Client::Client(string id, string name) : Entity(id), name(name) {}

Client::~Client() {
    
}

void Client::addWallet(shared_ptr<Wallet> wallet) {
    if (!wallet) {
        cerr << "Attempted to add nullptr wallet\n";
        return;
    }

    cout << "Client (" << name << ") adding wallet " << wallet->getId() << endl;
    wallets.addEntity(wallet);
}

const vector<shared_ptr<Entity>>& Client::getWallets() const {
    return wallets.getAllEntities();
}

double Client::getTotalBalance() const {
    double totalBalance = 0.0;
    const vector<shared_ptr<Entity>>& allWallets = wallets.getAllEntities();
    for (const auto& walletEntity : allWallets) {
        shared_ptr<Wallet> wallet = dynamic_pointer_cast<Wallet>(walletEntity);
        if (wallet) {
            totalBalance += wallet->getBalance();
        }
    }
    return totalBalance;
}

string Client::getId() const {
    return id;
}

string Client::getName() const {
    return name;
}

// Standart client
StandardClient::StandardClient(string id, string name) : Client(id, name) {}

double StandardClient::calculateCommission(double amount) const {
    return amount * 0.05; // 5% commission
}

double StandardClient::getMaxTransactionLimit() const {
    return 1000.0;
}

string StandardClient::getBenefits() const {
    return "Standard access";
}

// Golden client
GoldClient::GoldClient(string id, string name) : Client(id, name) {}

double GoldClient::calculateCommission(double amount) const {
    return amount * 0.01; // 1% commission
}

double GoldClient::getMaxTransactionLimit() const {
    return 10000.0;
}

string GoldClient::getBenefits() const {
    return "Priority processing, low commissions";
}

// Platinum client
PlatinumClient::PlatinumClient(string id,string name):Client(id , name){}

double PlatinumClient::calculateCommission(double amount)const{
    return amount * 0.02; //коммиссия два процента
}

double PlatinumClient::getMaxTransactionLimit()const{
    return 5000.0;
}

string PlatinumClient::getBenefits()const{
    return "бонусные награды, умеренная комиссия";
}

ClientNode::ClientNode(shared_ptr<Client> data)
: data(std::move(data)), left(nullptr), right(nullptr) {}

ClientNode::~ClientNode() {
    
}