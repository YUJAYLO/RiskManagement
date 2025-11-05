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

    // 讀取並解析 JSON 檔案
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
}

#endif