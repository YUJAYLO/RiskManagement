#ifndef STOCK_ID_H
#define STOCK_ID_H

#include <string>

class StockID {
private:
    std::string _id;

public:
    StockID();                      // Default constructor
    StockID(const std::string& id); // Initial constructor
    StockID(const StockID& other);  // Copy constructor

    StockID& operator=(const std::string& id);

    std::string toString() const;

    bool isValid();

    bool operator==(const StockID& other) const;
    bool operator<(const StockID& other) const;
};

#endif