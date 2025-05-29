#include "Blockchain.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>

using namespace std;
Blockchain::Blockchain() {}

Blockchain::~Blockchain() {}

bool Blockchain::removeTransaction(const Transaction& tx) {
    return transactions.removeTransaction(tx.getId());
}

void Blockchain::addClient(shared_ptr<Client> client) {
    clients.insert(client);
}

shared_ptr<Client> Blockchain::findClient(const string& clientId) const {
    return clients.find(clientId);
}

// Исправленный метод findWallet
shared_ptr<Wallet> Blockchain::findWallet(const string& walletId, const Client* client) const {
    if (client) {
        // Получаем сам объект Entityvector, затем вызываем на нем getEntity
        shared_ptr<Entity> walletEntity = client->getWalletsObject().getEntity(walletId);
        return dynamic_pointer_cast<Wallet>(walletEntity);
    }
    return nullptr;
}

bool Blockchain::processTransaction(const string& senderClientId, const string& senderWalletId,const string& receiverClientId, const string& receiverWalletId,double amount) {
    shared_ptr<Client> senderClient = findClient(senderClientId);
    shared_ptr<Client> receiverClient = findClient(receiverClientId);

    if (!senderClient || !receiverClient) {
        cout << "Error: The sender client or recipient client was not found." << endl;
        return false;
    }

    shared_ptr<Wallet> senderWallet = findWallet(senderWalletId, senderClient.get());
    shared_ptr<Wallet> receiverWallet = findWallet(receiverWalletId, receiverClient.get());

    if (!senderWallet || !receiverWallet) {
        cout << "Error: The sender's or recipient's wallet was not found." << endl;
        return false;
    }

    if (senderWallet->getBalance() < amount) {
        cout << "Mistake: There are insufficient funds in the sender's wallet." << endl;
        return false;
    }

    double commission = senderClient->calculateCommission(amount);
    double totalDeduction = amount + commission;

    if (senderWallet->getBalance() < totalDeduction) {
        cout << "Mistake: There are not enough funds for the transaction and the commission." << endl;
        return false;
    }

    if (amount > senderClient->getMaxTransactionLimit()) {
        cout << "Error: The transaction amount exceeds the limit for the sender." << endl;
        return false;
    }

    stringstream ss;
    ss << "tx_" << transactions.getSize() + 1;
    Transaction* newTransaction = new Transaction(
        ss.str(), senderWalletId, receiverWalletId, amount, Txtype::TRANSFER, commission);

    senderWallet->withdraw(totalDeduction);
    receiverWallet->deposit(amount);
    transactions.addTransaction(newTransaction);

    cout << "The transaction was completed successfully. ID: " << newTransaction->getId()
              << ", Amount: " << amount
              << ", Commission fee: " << commission << endl;
    return true;
}

void Blockchain::displayClients() const {
    cout << "--- Customers (sorted by total balance) ---" << endl;
    clients.displayInOrder();
    cout << "-----------------------------------------" << endl;
}

void Blockchain::displayTransactions() const {
    transactions.displayTransaction();
}

void Blockchain::saveClientsToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        const vector<shared_ptr<Client>>& allClients = clients.getAllClients();

        for (const auto& client : allClients) {
            file << client->getId() << "," << client->getName() << ",";
            // Получаем сам объект Entityvector для доступа к его методу getAllEntities
            const vector<shared_ptr<Entity>>& clientWallets = client->getWalletsObject().getAllEntities();
            file << clientWallets.size();
            for (const auto& walletEntity : clientWallets) {
                shared_ptr<Wallet> wallet = dynamic_pointer_cast<Wallet>(walletEntity);
                if (wallet) {
                    file << "," << wallet->getId() << "," << fixed << setprecision(2) << wallet->getBalance();
                }
            }
            file << "\n";
        }
        file.close();
        cout << "Customer data is saved in" << filename << endl;
    } else {
        cerr << "Error opening the file for writing: " << filename << endl;
    }
}

void Blockchain::loadClientsFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string segment;
            vector<string> data;

            while (getline(ss, segment, ',')) {
                data.push_back(segment);
            }

            if (data.size() < 3) {
                cerr << "Warning: Incorrect format of the client's data in the row (too few fields): " << line << endl;
                continue;
            }

            string id = data[0];
            string name = data[1];
            int numWallets = stoi(data[2]);

            shared_ptr<Client> client;

            if (id.rfind("gold", 0) == 0) {
                client = make_shared<GoldClient>(id, name);
            } else if (id.rfind("platinum", 0) == 0) {
                client = make_shared<PlatinumClient>(id, name);
            } else {
                client = make_shared<StandardClient>(id, name);
            }

            for (int i = 0; i < numWallets; ++i) {
                if ((3 + i * 2 + 1) < data.size()) {
                    string walletId = data[3 + i * 2];
                    double balance = stod(data[3 + i * 2 + 1]);
                    shared_ptr<Wallet> wallet = make_shared<Wallet>(walletId, id, balance);
                    client->addWallet(wallet);
                } else {
                    cerr << "Warning: Incomplete wallet data for the client" << id << "in the line: " << line << endl;
                    break;
                }
            }
            addClient(client);
        }
        file.close();
        cout << "Customer data is downloaded from: " << filename << endl;
    } else {
        cerr << "Error opening the file for reading: " << filename << endl;
    }
}

void Blockchain::loadTransactionsFromFile(const string& filename) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string segment;
            vector<string> data;
            while (getline(ss, segment, ',')) {
                data.push_back(segment);
            }

            if (data.size() == 6) {
                string transactionId = data[0];
                string senderWalletId = data[1];
                string receiverWalletId = data[2];
                double amount = stod(data[3]);
                int typeInt = stoi(data[4]);
                double commission = stod(data[5]);

                Txtype type = static_cast<Txtype>(typeInt);
                Transaction* transaction = new Transaction(transactionId, senderWalletId, receiverWalletId, amount, type, commission);
                transactions.addTransaction(transaction);
            } else {
                cerr << "Warning: Incorrect format of the transaction data in the row: " << line << endl;
            }
        }
        inputFile.close();
        cout << "Transaction data is downloaded from: " << filename << endl;
    } else {
        cerr << "Error opening the file for reading: " << filename << endl;
    }
}

void Blockchain::saveTransactionsToFile(const string& filename) const {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        const TransactionNode* current = transactions.getHead();
        while (current != nullptr) {
            outputFile << current->data->getId() << ","
                       << current->data->getSenderWalletId() << ","
                       << current->data->getReceiveWalletId() << ","
                       << fixed << setprecision(2) << current->data->getAmount() << ","
                       << static_cast<int>(current->data->getType()) << ","
                       << fixed << setprecision(2) << current->data->getCommission() << "\n";
            current = current->next;
        }
        outputFile.close();
        cout << "Transaction data is downloaded to: " << filename << endl;
    } else {
        cerr << "Error opening the file for writing: " << filename << endl;
    }
}
