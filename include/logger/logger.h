#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
    private:
        std::string _logFilePath;
        std::ofstream _logFile;  
        
        std::string getCurrentTimestamp() const {
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            std::stringstream ss;
            ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
            return ss.str();
        }

    public:
        Logger(const std::string& logFilePath = "logs/trading.log") 
            : _logFilePath(logFilePath) {
            _logFile.open(_logFilePath, std::ios::app);
            if (!_logFile.is_open()) {
                throw std::runtime_error("Failed to open log file: " + _logFilePath);
            }
        }
        
        ~Logger() {
            if (_logFile.is_open()) {
                _logFile.close();
            }
        }
        
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        
        void logOrder(
            const std::string& brokerId,
            const std::string& accountNumber,
            const std::string& stockId,
            const std::string& price,
            const std::string& quantity,
            const std::string& orderType,
            const std::string& priceType,
            const std::string& status
        ) {
            
            if (!_logFile.is_open()) {
                throw std::runtime_error("Log file is not open");
            }
            
            _logFile << "==========================================\n";
            _logFile << "[" << getCurrentTimestamp() << "]\n";
            _logFile << "Broker ID: " << brokerId << "\n";
            _logFile << "Account: " << accountNumber << "\n";
            _logFile << "Stock ID: " << stockId << "\n";
            _logFile << "Price: " << price << "\n";
            _logFile << "Quantity: " << quantity << "\n";
            _logFile << "Order Type: " << orderType << "\n";
            _logFile << "Price Type: " << (priceType == "1" ? "Market" : "Limit") << "\n";
            _logFile << "Status: " << status << "\n";
            
            _logFile << "==========================================\n\n";
            
            _logFile.flush();
        }

        void log(const std::string& message, const std::string& level = "INFO") {
            if (!_logFile.is_open()) {
                throw std::runtime_error("Log file is not open");
            }
            
            _logFile << "[" << getCurrentTimestamp() << "] [" << level << "] " 
                    << message << "\n";
            
            _logFile.flush();
        }
};

#endif