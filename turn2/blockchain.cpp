#include "blockchain.hpp"
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
        cout << "Ошибка: Клиент-отправитель или клиент-получатель не найден." << endl;
        return false;
    }

    shared_ptr<Wallet> senderWallet = findWallet(senderWalletId, senderClient.get());
    shared_ptr<Wallet> receiverWallet = findWallet(receiverWalletId, receiverClient.get());

    if (!senderWallet || !receiverWallet) {
        cout << "Ошибка: Кошелек отправителя или получателя не найден." << endl;
        return false;
    }

    if (senderWallet->getBalance() < amount) {
        cout << "Ошибка: Недостаточно средств в кошельке отправителя." << endl;
        return false;
    }

    double commission = senderClient->calculateCommission(amount);
    double totalDeduction = amount + commission;

    if (senderWallet->getBalance() < totalDeduction) {
        cout << "Ошибка: Недостаточно средств для транзакции и комиссии." << endl;
        return false;
    }

    if (amount > senderClient->getMaxTransactionLimit()) {
        cout << "Ошибка: Сумма транзакции превышает лимит для отправителя." << endl;
        return false;
    }

    stringstream ss;
    ss << "tx_" << transactions.getSize() + 1;
    Transaction* newTransaction = new Transaction(
        ss.str(), senderWalletId, receiverWalletId, amount, Txtype::TRANSFER, commission);

    senderWallet->withdraw(totalDeduction);
    receiverWallet->deposit(amount);
    transactions.addTransaction(newTransaction);

    cout << "Транзакция успешно выполнена. ID: " << newTransaction->getId()
              << ", Сумма: " << amount
              << ", Комиссия: " << commission << endl;
    return true;
}

void Blockchain::displayClients() const {
    cout << "--- Клиенты (отсортировано по общему балансу) ---" << endl;
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
        cout << "Данные клиентов сохранены в " << filename << endl;
    } else {
        cerr << "Ошибка открытия файла для записи: " << filename << endl;
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
                cerr << "Предупреждение: Неверный формат данных клиента в строке (слишком мало полей): " << line << endl;
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
                    cerr << "Предупреждение: Неполные данные кошелька для клиента " << id << " в строке: " << line << endl;
                    break;
                }
            }
            addClient(client);
        }
        file.close();
        cout << "Данные клиентов загружены из " << filename << endl;
    } else {
        cerr << "Ошибка открытия файла для чтения: " << filename << endl;
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
                cerr << "Предупреждение: Неверный формат данных транзакции в строке: " << line << endl;
            }
        }
        inputFile.close();
        cout << "Данные транзакций загружены из " << filename << endl;
    } else {
        cerr << "Ошибка открытия файла для чтения: " << filename << endl;
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
        cout << "Данные транзакций сохранены в " << filename << endl;
    } else {
        cerr << "Ошибка открытия файла для записи: " << filename << endl;
    }
}
