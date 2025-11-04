#ifndef CLIENT_H
#define CLIENT_H

#include "../common/brokerID.h"
#include "../common/tradingAccount.h"
#include "../inventory/inventory.h"

#include <map>
#include <string>

class Client {
    private:
        BrokerId _brokerID;             
        TradingAccount _tradingAccount; 
        bool account_status_;           // Open account flag
        int trading_quota_;             
        int used_quota_;                
        Inventory inventory_;           // Inventory data
        
    public:
        Client(const BrokerId& broker_id,
                const TradingAccount& trading_account,
                bool account_status,
                int trading_quota,
                int used_quota,
                Inventory inventory
            );
};

#endif