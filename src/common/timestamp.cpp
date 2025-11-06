#include "../../include/common/timestamp.h"

#include <stdexcept>
#include <iomanip>
#include <sstream>

TimeStamp::TimeStamp(){ // Default constructor
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

std::string TimeStamp::toString() const{
    std::ostringstream oss;
    oss << std::setfill('0');  
    oss << std::setw(2) << _timestamp.HH << ":"
        << std::setw(2) << _timestamp.MM << ":"
        << std::setw(2) << _timestamp.SS << "."
        << std::setw(3) << _timestamp.mmm;
    return oss.str();
}

bool TimeStamp::isValid(int HH, int MM, int SS, int mmm) const{
    if(HH < 0 || HH > 23) return false;
    if(MM < 0 || MM > 59) return false;
    if(SS < 0 || SS > 59) return false;
    if(mmm < 0 || mmm > 999) return false;
    
    return true;
}