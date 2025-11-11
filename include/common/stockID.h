#ifndef STOCK_ID_H
#define STOCK_ID_H

#include <string>

class StockID {
private:
    std::string _id;
    
    bool isValid();

public:
    StockID(const std::string& id); // Initial constructor
    StockID(const StockID& other);  // Copy constructor

    std::string toString() const;
};

#endif