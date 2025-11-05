#ifndef TIME_STAMP_H
#define TIME_STAMP_H

#include <string>
#include <chrono>

class TimeStamp {
    private:
        struct TimeData {  
            int HH;
            int MM;
            int SS;
            int mmm;
        };
        TimeData _timestamp;

        bool isValid(int HH, int MM, int SS, int mmm) const;

    public:
        TimeStamp(const std::string& timeStampStr);

        std::string toString() const;
};

#endif