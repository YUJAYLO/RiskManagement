#include "../../include/common/timestamp.h"

#include <ctime>
#include <stdexcept>
#include <iomanip>
#include <sstream>

Timestamp::Timestamp(){ // Default constructor
    // Use current system time as the default timestamp
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ) % 1000;
    
    std::tm* local_time = std::localtime(&now_time_t);
    
    _timestamp.HH = local_time->tm_hour;
    _timestamp.MM = local_time->tm_min;
    _timestamp.SS = local_time->tm_sec;
    _timestamp.mmm = static_cast<int>(now_ms.count());
}

Timestamp::Timestamp(int HH, int MM, int SS, int mmm) // Initial constructor
    : _timestamp{HH, MM, SS, mmm} {
    if(!isValid(HH, MM, SS, mmm)){
        throw std::invalid_argument("Invalid Timestamp.");
    }
}

Timestamp::Timestamp(const Timestamp& other) // Copy constructor
    : _timestamp(other._timestamp) {}

Timestamp& Timestamp::operator=(const std::string& timeStr){ // Assignment from string
    // Expected format: "HH:MM:SS.mmm"
    if(timeStr.length() != 12 || timeStr[2] != ':' || timeStr[5] != ':' || timeStr[8] != '.'){
        throw std::invalid_argument("Invalid Timestamp string format. Expected: HH:MM:SS.mmm");
    }

    // Parse components
    int HH, MM, SS, mmm;
    try {
        HH = std::stoi(timeStr.substr(0, 2));
        MM = std::stoi(timeStr.substr(3, 2));
        SS = std::stoi(timeStr.substr(6, 2));
        mmm = std::stoi(timeStr.substr(9, 3));
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid Timestamp string: cannot parse numeric values");
    }

    // Create temporary to validate before modifying current object
    Timestamp temp(HH, MM, SS, mmm);
    _timestamp = temp._timestamp;
    
    return *this;
}

std::string Timestamp::toString() const{
    // Format Output: "HH:MM:SS.mmm" with leading zeros
    std::ostringstream oss;
    oss << std::setfill('0');  
    oss << std::setw(2) << _timestamp.HH << ":"
        << std::setw(2) << _timestamp.MM << ":"
        << std::setw(2) << _timestamp.SS << "."
        << std::setw(3) << _timestamp.mmm;
    return oss.str();
}

bool Timestamp::isValid(int HH, int MM, int SS, int mmm) const{
    if(HH < 0 || HH > 23) return false;
    if(MM < 0 || MM > 59) return false;
    if(SS < 0 || SS > 59) return false;
    if(mmm < 0 || mmm > 999) return false;
    
    return true;
}