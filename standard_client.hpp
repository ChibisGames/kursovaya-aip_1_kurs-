
#ifndef standard_client_hpp
#define standard_client_hpp

#include <iostream>
#include <string>
#include "client (2).hpp"
using namespace std;


class StandardClient : public Client{
public:
    StandardClient(string id, string name);
    double calculateCommission(double amount) const override;
    double getMaxTransactionLimit()const override;
    string getBenefits() const;
    ~StandardClient()override{}
};
#endif /* standard_client_hpp */
