#ifndef CLIENT_H
#define CLIENT_H

#include "../common/brokerID.h"
#include "../common/tradingAccount.h"
#include "../inventory/inventory.h"

class Client{
    public:
        enum class accountFlag : char{ 
            OPENED = 'Y', 
            CLOSED = 'E', 
            NOT_OPENED = ' '
        };

    private:
        BrokerId _brokerID;             
        TradingAccount _tradingAccount; 
        accountFlag accountFlag_;           // Open account flag
        int tradingQuota_;             
        int usedQuota_;                
        Inventory inventory_;           // Inventory data
        
    public:
        Client(const BrokerId& broker_id,
                const TradingAccount& trading_account,
                accountFlag accountFlag,
                int tradingQuota,
                int usedQuota,
                Inventory inventory
            );
};

#endif