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
        accountFlag _accountFlag;       // Open account flag
        int _tradingQuota;             
        int _usedQuota;                
        Inventory _inventory;           // Inventory data
        
    public:
        Client( const BrokerId& broker_id,
                const TradingAccount& trading_account);

        // Getters
        inline char getAccountFlag() const { return static_cast<char>(_accountFlag); }
};

#endif