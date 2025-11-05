#ifndef PRICE_H
#define PRICE_H

#include <string>

class Price {
private:
    int _price; // 實際值* 10000

public:
    Price();                        // Default constructor
    Price(const Price& other);      // Copy constructor
    Price(const std::string& priceStr);  // Initial constructor

    Price& operator=(const std::string& priceStr);

    
    std::string toString() const;
};

#endif