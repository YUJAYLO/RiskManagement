#ifndef STOCK_ID_H
#define STOCK_ID_H

#include <string>

class StockId {
private:
    std::string _id;

public:
    StockId();                      // Default constructor
    StockId(const std::string& id); // Initial constructor
    StockId(const StockId& other);  // Copy constructor

    StockId& operator=(const std::string& id);

    std::string toString() const;

    bool isValid();

    bool operator==(const StockId& other) const;
    bool operator<(const StockId& other) const;
};

#endif