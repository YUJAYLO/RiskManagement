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
        BrokerID _brokerID;             
        TradingAccount _tradingAccount; 
        accountFlag _accountFlag;       // Open account flag
        float _tradingQuota;             
        float _usedQuota;                
        Inventory _inventory;           // Inventory data
        
    public:
        Client( const BrokerID& broker_id,
                const TradingAccount& trading_account);

        void addUsedQuota(float amount) { _usedQuota += amount; }

        // Getters
        inline char getAccountFlag() const { return static_cast<char>(_accountFlag); }
        inline float getTradingQuota() const { return _tradingQuota; }
        inline float getUsedQuota() const { return _usedQuota; }
        inline const Inventory& getInventory() const { return _inventory; }
};

#endif