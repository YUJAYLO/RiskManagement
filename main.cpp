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
    
    std::cout << "=== Stock Trading System ===" << std::endl;
    std::cout << "=== Login ===" << std::endl; 
    
    std::string brokerId = getInput("Please enter your Broker ID: ");
    std::string accountNumber = getInput("Please enter your Trading Account Number: ");
    

    std::cout << "\nLogin successful! Welcome, " << brokerId << "-" << accountNumber << std::endl;
    std::cout << "You can now start placing orders.\n" << std::endl;
    
    while (true) {
        std::cout << "\n=== New Order ===" << std::endl;
        
        try {
            Order newOrder = Order(
                brokerId,  
                accountNumber,  
                getInput("Stock ID: "),
                getInput("Price: "),
                getInput("Quantity: "),
                getInput("Order Type (B/Buy or S/Sell): "),
                getInput("Price Type (1:Market or 2:Limit): ")
            );
            
            DataManager::updateClientInventory(
                brokerId,
                accountNumber,
                newOrder.getStockId(),
                newOrder.getQuantity(),
                newOrder.getOrderType()
            );
            std::cout << "✓ Order successfully created!" << std::endl;
            logger.logOrder(
                brokerId,
                accountNumber,
                newOrder.getStockId(),
                newOrder.getPrice(),
                newOrder.getQuantity(),
                newOrder.getOrderType(),
                newOrder.getPriceType(),
                "SUCCESS" // NEED DOUBLE CHECK
            );
            
        } catch (const std::exception& e) {
            std::cerr << "Order failed: " << e.what() << std::endl;
        }
        
        std::string continueOrder = getInput("\nDo you want to place another order? (Y/N): ");
        if (continueOrder != "Y" && continueOrder != "y") {
            std::cout << "\nThank you for using our trading system. Goodbye!" << std::endl;
            break;
        }
    }

    return 0;
}