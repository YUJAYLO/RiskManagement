#ifndef TIME_STAMP_H
#define TIME_STAMP_H

#include <string>
#include <chrono>

class Timestamp {
    private:
        struct TimeStamp {
            int HH;
            int MM;
            int SS;
            int mmm;
        };
        TimeStamp _timestamp;

        bool isValid(int HH, int MM, int SS, int mmm) const;

    public:
        Timestamp(); // Default constructor (current time)
        Timestamp(int HH, int MM, int SS, int mmm); // Initial constructor
        Timestamp(const Timestamp& other); // Copy constructor

        Timestamp& operator=(const std::string& timeStr);

        std::string toString() const;
};

#endif