#ifndef eniti_hpp
#define eniti_hpp
#include <string>
#include <memory> 
using namespace std;

class Entity {
protected:
    string id;
public:
    Entity(string id) : id(id) {}
    virtual ~Entity() {}
    virtual string getId() const {return id;}
};

#endif
