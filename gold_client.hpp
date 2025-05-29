#ifndef gold_client_hpp
#define gold_client_hpp

#include <string>
#include "client.hpp"
using namespace std;

class GoldClient : public Client{
public:
    GoldClient(string id, string name);
    double calculateCommission(double amount) const override;
    double getMaxTransactionLimit()const override;
    string getBenefits() const;
    ~GoldClient()override{}
};
#endif
