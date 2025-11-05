#ifndef ORDER_H
#define ORDER_H

#include "../common/brokerID.h"
#include "../common/tradingAccount.h"
#include "../common/stockID.h"
#include "../common/timestamp.h"
#include "../stock/stock.h"

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
        StockID _stockID;
        double _price; // 5 digits of integer and 4 digits of decimal
        int _quantity;
        OrderType _orderType;
        PriceType _priceType;
        Timestamp _orderTime;
        ForceFlagType _forceFlag;

    public:
        Order(
            const BrokerId& brokerId, 
            const TradingAccount& tradingAccount,
            const Stock& stock,
            double price,
            int quantity,
            OrderType ordertype,
            PriceType priceType,
            const Timestamp& orderTime,
            const ForceFlagType& forceFlag
        );

};

#endif