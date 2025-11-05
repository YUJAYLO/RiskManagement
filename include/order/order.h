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
        StockID _stockId;
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
            const std::string& priceTypeStr,
            const std::string& orderTimeStr,
            const std::string& forceFlagStr
        );
};

#endif