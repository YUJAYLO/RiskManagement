#ifndef ORDER_H
#define ORDER_H

#include "../common/brokerID.h"
#include "../common/Price.h"
#include "../common/tradingAccount.h"
#include "../common/stockID.h"
#include "../stockInfo/StockInfo.h"
#include "../common/timestamp.h"
#include "../stockInfo/StockInfo.h"

#include <string>

class Order{
    public:
        enum class OrderType : char{
            BUY = 'B',      
            SELL = 'S'      
        };

        enum class PriceType : int{ 
            Market = 1, 
            Limit = 2 
        };

        enum class ForceFlagType : char{
            FORCE = 'Y',    
            NO_FORCE = ' '  
        };

    private:
        BrokerId _brokerId;
        TradingAccount _tradingAccount;
        StockId _stockId;
        StockInfo _stockInfo;
        Price _price; // 5 digits of integer and 4 digits of decimal
        int _quantity;
        OrderType _orderType;
        PriceType _priceType;
        TimeStamp _orderTime;
        ForceFlagType _forceFlag;

    public:
        Order(
            const std::string& brokerTDStr,
            const std::string& accountNumStr,
            const std::string& stockIDStr,
            const std::string& priceStr,
            const std::string& quantityStr,
            const std::string& orderTypeStr,
            const std::string& priceTypeStr
        );

        // Getter Functions
        std::string getStockId() const { return _stockId.toString(); }
        std::string getPrice() const { return _price.toString(); }
        std::string getQuantity() const { return std::to_string(_quantity); };
        std::string getOrderType() const { 
            return (_orderType == OrderType::BUY) ? "BUY" : "SELL"; 
        };
        std::string getPriceType() const { 
            return (_priceType == PriceType::Market) ? "Market" : "Limit"; 
        }; 
};

#endif