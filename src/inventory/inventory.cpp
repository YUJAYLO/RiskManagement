#include "../../include/inventory/inventory.h"

#include <iostream>

InventoryItem::InventoryItem()
    : _stockID(""), _totalShares(0), _usedShares(0) {} // 預設值

InventoryItem::InventoryItem(const std::string& stockID, const std::string& totalShares, const std::string& usedShares){
    _stockID = StockID(stockID);
    _totalShares = std::stoi(totalShares);
    _usedShares = std::stoi(usedShares);
}

Inventory::Inventory(const std::vector<InventoryItem>& items) {
    for(const InventoryItem& item : items){
        _inventoryStock[item.getStockID().toString()] = item;
    }
}

bool InventoryItem::hasEnoughShares(int requiredShares) const {
    return getAvailableShares() >= requiredShares;
}

bool InventoryItem::addShares(int shares) {
    if (shares < 0) 
        return false;
    _totalShares += shares;
    return true;
}

bool InventoryItem::useShares(int shares) {
    if (shares < 0 || shares > getAvailableShares()) return false;
    _usedShares += shares;
    return true;
}

bool InventoryItem::releaseShares(int shares) {
    if (shares < 0 || shares > _usedShares) return false;
    _usedShares -= shares;
    return true;
}

void Inventory::add(const InventoryItem& item) {
    if(!hasStock(item.getStockID())) // Only add if stockID does not exist in the inventory
        _inventoryStock[item.getStockID().toString()] = item;
}

bool Inventory::hasStock(const StockID& stockID) const {
    return _inventoryStock.find(stockID.toString()) != _inventoryStock.end();
}

// Assumes stockID exists
bool Inventory::hasEnoughShares(const StockID& stockID, int requiredShares) const {
    auto it = _inventoryStock.find(stockID.toString()); 
    return it->second.hasEnoughShares(requiredShares); 
}

bool Inventory::addShares(const StockID& stockID, int shares) {
    auto it = _inventoryStock.find(stockID.toString());
    return it->second.addShares(shares);
}

bool Inventory::useShares(const StockID& stockID, int shares) {
    auto it = _inventoryStock.find(stockID.toString());
    return it->second.useShares(shares);
}

bool Inventory::releaseShares(const StockID& stockID, int shares) {
    auto it = _inventoryStock.find(stockID.toString());
    return it->second.releaseShares(shares);
}

const InventoryItem* Inventory::get(const StockID& stockID) const {
    auto it = _inventoryStock.find(stockID.toString());
    if (it == _inventoryStock.end()) return nullptr;
    return &(it->second);
}

void Inventory::printInventory() const {
    std::cout << "----- Inventory -----" << std::endl;
    for (const auto& pair : _inventoryStock) {
        const InventoryItem& item = pair.second;
        std::cout << "StockID: " << item.getStockID().toString()
                  << ", Total Shares: " << item.getTotalShares()
                  << ", Used Shares: " << item.getUsedShares()
                  << ", Available Shares: " << item.getAvailableShares()
                  << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}

