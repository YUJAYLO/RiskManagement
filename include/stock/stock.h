#ifndef STOCK_H
#define STOCK_H

#include "../common/stockID.h"

class Stock{
    private:
        StockID _stockID;
        double _price;

    public:
        Stock(double price) : _price(price) {}

        bool isBetweenLimit(double price) const;
        
        // Getter
        double getPrice() const { return _price; }
        StockID& getStockID() const { return ; } // 假設有一個 StockID 類別;
};

#endif