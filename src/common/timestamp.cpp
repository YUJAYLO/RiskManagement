#include "../../include/common/timeStamp.h"

#include <stdexcept>
#include <iomanip>
#include <sstream>

TimeStamp::TimeStamp(const std::string& timeStampStr){
    // Expected format: "HH:MM:SS.mmm"
    if(timeStampStr.length() != 12 || timeStampStr[2] != ':' || 
       timeStampStr[5] != ':' || timeStampStr[8] != '.'){
        throw std::invalid_argument("Invalid Timestamp string format. Expected: HH:MM:SS.mmm");
    }

    // Parse components
    int HH, MM, SS, mmm;
    try {
        HH = std::stoi(timeStampStr.substr(0, 2));
        MM = std::stoi(timeStampStr.substr(3, 2));
        SS = std::stoi(timeStampStr.substr(6, 2));
        mmm = std::stoi(timeStampStr.substr(9, 3));
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid Timestamp string: cannot parse numeric values");
    }

    // Validate before setting
    if(!isValid(HH, MM, SS, mmm)){
        throw std::invalid_argument("Invalid Timestamp values.");
    }
    
    _timestamp = {HH, MM, SS, mmm};
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