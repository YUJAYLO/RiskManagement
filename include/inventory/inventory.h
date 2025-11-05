#ifndef INVENTORY_H
#define INVENTORY_H

#include "../common/stockID.h"
#include <unordered_map>
#include <vector>

/*
    Here we define two classes: InventoryItem and Inventory.
    InventoryItem represents an individual stock holding, tracking total shares and used shares and provides methods to manage shares.
    But InventoryItem's methods are private, ensuring only Inventory can modify them.
    Inventory manages a collection of InventoryItems, allowing addition of new items and share management through public methods. 
    This design encapsulates inventory management while restricting direct access to individual item details.
*/
class InventoryItem {
    private:
        StockID _stockID; 
        int _totalShares; // Total shares held
        int _usedShares; // Shares currently committed or used

        // For Inventory to access item details
        const StockID& getStockID() const { return _stockID; }
        int getTotalShares() const { return _totalShares; }
        int getUsedShares() const { return _usedShares; }
        int getAvailableShares() const { return _totalShares - _usedShares; }
        
        // For Inventory to manage shares
        bool hasEnoughShares(int requiredShares) const;
        bool addShares(int shares);
        bool useShares(int shares);
        bool releaseShares(int shares);

    public:
        InventoryItem(const StockID& stockID, int totalShares, int usedShares)
            : _stockID(stockID), _totalShares(totalShares), _usedShares(usedShares){};

        friend class Inventory;
};

class Inventory {
    private:
        std::unordered_map<std::string, InventoryItem> _inventoryStock; // key: stockID

    public:
        Inventory() = default; // Default constructor, for new user with empty inventory
        Inventory(const std::vector<InventoryItem>& items);

        // Add a new inventory item
        void add(const InventoryItem& item);
        
        // Inventory management methods
        bool hasStock(const StockID& stockID) const;                            // Check if stock exists
        bool hasEnoughShares(const StockID& stockID, int requiredShares) const; // Check if enough shares are available
        bool addShares(const StockID& stockID, int shares);                     // Add shares to inventory after buy
        bool useShares(const StockID& stockID, int shares);                     // Commit shares for selling
        bool releaseShares(const StockID& stockID, int shares);                 // Release committed shares after sell or cancel
        
        // Query methods(read-only)
        const InventoryItem* get(const StockID& stockID) const;
        const std::unordered_map<std::string, InventoryItem>& getAllInventory() const { return _inventoryStock; }
        void printInventory() const;
        
        // Clear inventory
        void clear() { _inventoryStock.clear(); }
};

#endif