//
//  TransactionNode.hpp
//  курсовая
//
//  Created by Ваграм on 5/15/25.
//

#ifndef TransactionNode_hpp
#define TransactionNode_hpp
#include "transaction.hpp"
using namespace std;

class TransactionNode {
public:
    Transaction* data;
    TransactionNode* prev;
    TransactionNode* next;
    TransactionNode(Transaction* data);
    ~TransactionNode();
};
#endif /* TransactionNode_hpp */
