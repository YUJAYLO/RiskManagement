#ifndef BROKER_ID_H
#define BROKER_ID_H

#include <string>

class BrokerId {
    private:
        std::string _id; 

    public:
        BrokerId(); // Default constructor
        BrokerId(const std::string& id); // Initial constructor
        BrokerId(const BrokerId& other); // Copy constructor

        BrokerId& operator=(const std::string& id);

        std::string toString() const;

        bool isValid() const;

        bool operator==(const BrokerId& other) const;
        bool operator<(const BrokerId& other) const;
};

#endif 