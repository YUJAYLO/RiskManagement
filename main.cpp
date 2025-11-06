#include <iostream>
#include <string>
#include "./include/manager/dataManager.h"
#include "./include/order/order.h"
#include "./logs/logger.h"


int main(){
    Logger logger("logs/trading.log");

    auto getInput = [](const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        std::cin >> input;
        return input;
    };
    
    std::string func;
    while (true) {
        std::cout << "Enter function (order/query stock/ query client information/ exit): " << std::endl;
        std::cin >> func;
        
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
            
            DataManager::updateClientInventory(
                newOrder.getBrokerId(),
                newOrder.getAccountNumber(),
                newOrder.getStockId(),
                newOrder.getQuantity(),
                newOrder.getOrderType()
            );

            std::cout << "✓ Order successfully created!" << std::endl;
            logger.logOrder(
                newOrder.getBrokerId(),
                newOrder.getAccountNumber(),
                newOrder.getStockId(),
                newOrder.getPrice(),
                newOrder.getQuantity(),
                newOrder.getOrderType(),
                newOrder.getPriceType(),
                "SUCCESS" // NEED DOUBLE CHECK
            );
            
        } catch (const std::exception& e) {
            logger.log(
                std::string("Order failed: ") + e.what(),
                "FAILED"
            );
        }
        

    }

    return 0;
}