#pragma once

#include <vector>
#include <memory> // для shared_ptr
#include <string>

#include "client.hpp"
using namespace std;

class ClientBST {
private:
    ClientNode* root;

    void insert(ClientNode*& node, shared_ptr<Client> client);
    bool remove(ClientNode*& node, const string& id);
    void destroyTree(ClientNode* node);
    void displayInOrder(ClientNode* node) const;
    void inOrderTraversal(ClientNode* node, vector<shared_ptr<Client>>& clients) const;
    shared_ptr<Client> find(ClientNode* node, const string& id) const;
    ClientNode* findMin(ClientNode* node) const;

public:
    ClientBST();
    ~ClientBST();

    void insert(shared_ptr<Client> client);
    bool remove(const string& id);
    void displayInOrder() const;
    vector<shared_ptr<Client>> getAllClients() const;
    shared_ptr<Client> find(const string& id) const;
};
