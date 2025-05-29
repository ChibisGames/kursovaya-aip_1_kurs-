#ifndef client_node_hpp
#define client_node_hpp

#include <memory> // для shared_ptr
#include "client.hpp"
using namespace std;

class ClientNode {
public:
    shared_ptr<Client> data;
    ClientNode* left;
    ClientNode* right;

    ClientNode(shared_ptr<Client> data);
    ~ClientNode();
};
#endif 
