#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "../utils/json.hpp"

#include <string>
#include <tuple>
#include <fstream>
#include <sstream>
#include <stdexcept>


using json = nlohmann::json;

namespace DataManager {
    inline std::string getDataPath() {
        return "data/";
    }

    inline json loadAndParseJson(const std::string& filename, const std::string& basePath = "") {
        std::string filepath;
        if (basePath.empty()) {
            filepath = getDataPath() + filename;
        } else {
            filepath = basePath + (basePath.back() == '/' ? "" : "/") + filename;
        }
        
        std::ifstream file(filepath);
        
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filepath);
        }
        
        json jsonData;
        try {
            file >> jsonData;
        } catch (const json::parse_error& e) {
            throw std::runtime_error("JSON parse error in " + filepath + ": " + e.what());
        }
        
        return jsonData;
    }

    // fetch stock data from stock.json by stockId
    inline std::tuple<std::string, std::string, std::string> fetchStockData(const std::string& stockIdStr) {
        json jsonData = loadAndParseJson("stock.json");

        if (!jsonData.contains(stockIdStr)) {
            throw std::runtime_error("Stock ID not found: " + stockIdStr);
        }
        
        auto stockData = jsonData[stockIdStr];
        
        std::string stockNameStr = stockData.value("stockName", "");
        std::string stockPriceStr = stockData.value("stockPrice", "");
        std::string stageStr = stockData.value("stageStr", "");
        
        return std::make_tuple(stockNameStr, stockPriceStr, stageStr);
    }

    // fetch client info from client_info.json by brokerId and accountNumber
    inline std::tuple<std::string, std::string, std::string> fetchClientInfo(const std::string& brokerIdStr, const std::string& accountNumberStr) {
        json jsonData = loadAndParseJson("client_info.json");
        
        std::string key = brokerIdStr + "-" + accountNumberStr;
        
        if (!jsonData.contains(key)) {
            throw std::runtime_error("Client not found: " + key);
        }
        
        auto clientData = jsonData[key];
        
        // accountFlag: "Y" (OPENED), "E" (CLOSED), " " (NOT_OPENED)
        std::string accountFlagStr = clientData.value("accountFlag", " ");
        std::string tradingQuotaStr = clientData.value("tradingQuota", "0");
        std::string usedQuotaStr = clientData.value("usedQuota", "0");
        
        return std::make_tuple(accountFlagStr, tradingQuotaStr, usedQuotaStr);
    }

    // update client info in client_info.json before order executed
    inline void updateClientInfo(
        const std::string& brokerIdStr, 
        const std::string& accountNumberStr,
        const float& addUsedQuotaStr) {
        json jsonData = loadAndParseJson("client_info.json");
        
        std::string key = brokerIdStr + "-" + accountNumberStr;
        
        if (!jsonData.contains(key)) {
            throw std::runtime_error("Client not found: " + key);
        }
        
        float currentUsedQuota = jsonData[key]["usedQuota"].get<float>();
        currentUsedQuota += addUsedQuotaStr;
        jsonData[key]["usedQuota"] = std::to_string(currentUsedQuota);
        
        std::string filepath = getDataPath() + "client_info.json";
        std::ofstream file(filepath);
        
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for writing: " + filepath);
        }
        
        file << jsonData.dump(2); 
        file.close();
    }

    // fetch client inventory from client_inventory.json by brokerId and accountNumber
    inline std::vector<std::tuple<std::string, std::string, std::string>> fetchClientInventory(const std::string& brokerIdStr, const std::string& accountNumberStr) {
        json jsonData = loadAndParseJson("client_inventory.json");
        
        std::string key = brokerIdStr + "-" + accountNumberStr;
        
        if (!jsonData.contains(key)) {
            throw std::runtime_error("Client inventory not found: " + key);
        }
        
        auto inventoryArray = jsonData[key];
        
        if (!inventoryArray.is_array()) {
            throw std::runtime_error("Invalid inventory data format for: " + key);
        }
        
        std::vector<std::tuple<std::string, std::string, std::string>> inventoryList;
        
        for (const auto& item : inventoryArray) {
            std::string stockIdStr = item.value("stockId", "");
            std::string totalSharesStr = item.value("totalShares", "0");
            std::string usedSharesStr = item.value("usedShares", "0");
            
            inventoryList.push_back(std::make_tuple(stockIdStr, totalSharesStr, usedSharesStr));
        }
        
        return inventoryList;
    }

    // update client inventory in client_inventory.json after order executed   
    inline void updateClientInventory(
        const std::string& brokerIdStr, 
        const std::string& accountNumberStr,
        const std::string& stockIdStr,
        const std::string& quantityStr,
        const std::string& OrderTypeStr) {
        json jsonData = loadAndParseJson("client_inventory.json");
        
        std::string key = brokerIdStr + "-" + accountNumberStr;
        
        // Created new client inventory if not exists
        if (!jsonData.contains(key)) {
            jsonData[key] = json::array();
        }
        
        // Find if the stock already exists
        bool stockFound = false;
        for (auto& item : jsonData[key]) {
            if (item["stockId"] == stockIdStr) {
                if (OrderTypeStr == "BUY") {
                    int updatedTotalShares = item["totalShares"].get<int>() + std::stoi(quantityStr);
                    item["totalShares"] = std::to_string(updatedTotalShares);
                } else { // SELL
                    int updatedTotalShares = item["totalShares"].get<int>() - std::stoi(quantityStr);
                    item["totalShares"] = std::to_string(updatedTotalShares);
                }
                stockFound = true;
                break;
            }
        }
        
        // Create new stock entry if not found (Buy new stock only)
        if (!stockFound) { 
            json newStock = {
                {"stockId", stockIdStr},
                {"totalShares", quantityStr},
                {"usedShares", 0}
            };
            jsonData[key].push_back(newStock);
        }
        
        std::string filepath = getDataPath() + "client_inventory.json";
        std::ofstream file(filepath);
        
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for writing: " + filepath);
        }
        
        file << jsonData.dump(2); 
        file.close();
    }
}

#endif