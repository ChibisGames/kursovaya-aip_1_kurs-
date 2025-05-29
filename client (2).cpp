#include "client.hpp"
#include "wallet.hpp"
#include <iostream> // For cout, cerr
#include <memory> // For dynamic_pointer_cast

using namespace std; // Added for the requested removal of std::

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
