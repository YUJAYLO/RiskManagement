#ifndef STOCK_DATA_MANEGER_H
#define STOCK_DATA_MANAGER_H

#include <string>
#include <tuple>

class StockDataManager{
    private:
        
    public:
        StockDataManager();

        std::tuple<std::string, std::string, std::string, std::string> fetchData(const std::string& stockId); 
};

#endif