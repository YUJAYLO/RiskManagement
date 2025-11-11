#include <iostream>
#include <string>
#include <tuple>
#include "./include/manager/dataManager.h"
#include "./include/order/order.h"
#include "./include/logger/logger.h"


int main(){
    Logger logger("logs/trading.log");

    auto getInput = [](const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input); // 使用 getline 讀取整行輸入
        return input;
    };
    
    std::string func;
    while (true) {
        std::cout << "\nEnter function (O:order/ QS:query stock/ QC:query client information/ E:exit): ";
        std::getline(std::cin, func);

        if(func == "O"){
            try {
                Order newOrder = Order(
                    getInput("Broker ID: "),  
                    getInput("Trading Account Number: "),  
                    getInput("Stock ID: "),
                    getInput("Price: "),
                    getInput("Quantity: "),
                    getInput("Order Type (B/Buy or S/Sell): "),
                    getInput("Price Type (1:Market or 2:Limit): "),
                    getInput("ForceFlag (Y:Force or N:NoForce): ")
                );

                // Update client info and inventory
                DataManager::updateClientInfo(
                    newOrder.getBrokerId(),
                    newOrder.getAccountNumber(),
                    newOrder.getOrderCost()
                );
                
                DataManager::updateClientInventory(
                    newOrder.getBrokerId(),
                    newOrder.getAccountNumber(),
                    newOrder.getStockId(),
                    newOrder.getQuantity(),
                    newOrder.getOrderType()
                );

                std::cout << "Order successfully created!" << std::endl;
                logger.logOrder(
                    newOrder.getBrokerId(),
                    newOrder.getAccountNumber(),
                    newOrder.getStockId(),
                    newOrder.getPrice(),
                    newOrder.getQuantity(),
                    newOrder.getOrderType(),
                    newOrder.getPriceType(),
                    "SUCCESS" 
                );
            } catch (const std::exception& e) {
                logger.log(
                    std::string("Order failed: ") + e.what(),
                    "FAILED"
                );
                std::cout << "Error: " << e.what() << std::endl;
            }
        } else if(func == "QS"){
            try{
                auto [stockName, stockPrice, stage] = DataManager::fetchStockData(getInput("Stock ID: "));
                std::cout << "\n=== Stock Information ===" << std::endl;
                std::cout << "  Stock Name: " << stockName << std::endl;
                std::cout << "  Stock Price: " << stockPrice << std::endl;
                std::cout << "  Stage: " << stage << std::endl;
            } catch (const std::exception& e){
                logger.log(
                    std::string("Query stock failed: ") + e.what(), 
                    "FAILED"
                );
            }
        } else if(func == "QC"){
            std::string brokerId = getInput("Broker ID: ");
            std::string accountNumber = getInput("Account Number: ");
            
            try {
                // Fetch client info
                auto [accountFlag, tradingQuota, usedQuota] = DataManager::fetchClientInfo(brokerId, accountNumber);
                
                std::cout << "\n=== Client Information ===" << std::endl;
                std::cout << "  Account Status: ";
                if (accountFlag == "Y") {
                    std::cout << "OPENED" << std::endl;
                } else if (accountFlag == "E") {
                    std::cout << "CLOSED" << std::endl;
                } else {
                    std::cout << "NOT_OPENED" << std::endl;
                }
                std::cout << "  Trading Quota: " << tradingQuota << std::endl;
                std::cout << "  Used Quota: " << usedQuota << std::endl;
                
                // Fetch client inventory
                auto inventoryList = DataManager::fetchClientInventory(brokerId, accountNumber);
                
                std::cout << "\n=== Client Inventory ===" << std::endl;
                if (inventoryList.empty()) {
                    std::cout << "  No stocks in inventory" << std::endl;
                } else {
                    for (const auto& [stockId, totalShares, usedShares] : inventoryList) {
                        std::cout << "  Stock ID: " << stockId << std::endl;
                        std::cout << "  Total Shares: " << totalShares << std::endl;
                        std::cout << "  Used Shares: " << usedShares << std::endl;
                        std::cout << "  Available Shares: " << (std::stoi(totalShares) - std::stoi(usedShares)) << std::endl;
                        std::cout << "  ---" << std::endl;
                    }
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
                logger.log(
                    std::string("Query client failed: ") + e.what(), 
                    "FAILED"
                );
            }
        } else if(func == "E"){
            break; //Exit the program
        } else {
            std::cout << "Invalid function. Please try again." << std::endl;
        }
    }

    return 0;
}