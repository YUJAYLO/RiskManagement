#ifndef BROKER_ID_H
#define BROKER_ID_H

#include <string>

class BrokerID {
    private:
        std::string _id;
        
        bool isValid() const;

    public:
        BrokerID(const std::string& id) : _id(id){}; // Initial constructor

        std::string toString() const;
};

#endif 