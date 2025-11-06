#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <algorithm>
#include <cctype>

namespace StringUtils {
    inline bool isAlphanumeric(const std::string& str) {
        return std::all_of(str.begin(), str.end(), [](char c){
            return std::isalnum(static_cast<unsigned char>(c));
        });
    }

    inline bool isLengthInRange(const std::string& str, size_t minLen, size_t maxLen) {
        return str.length() >= minLen && str.length() <= maxLen;
    }

    inline bool isNumeric(const std::string& str) {
        return std::all_of(str.begin(), str.end(), [](char c){
            return std::isdigit(static_cast<unsigned char>(c));
        });
    }

    inline std::string toUpperCase(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), 
            [](unsigned char c){ return std::toupper(c); });
        return result;
    }

    inline int getCharPriority(char c) {
        if (std::isdigit(c)) {
            return c - '0'; 
        } else if (std::isupper(c)) {
            return 10 + (c - 'A');  
        } else if (std::islower(c)) {
            return 36 + (c - 'a');  
        }
    }

    // "Lower than" logic between IDs(Broker IDs, Stock IDs)
    inline bool IDCompare(const std::string& str1, const std::string& str2) {
        size_t minLen = std::min(str1.length(), str2.length());
        
        for (size_t i = 0; i < minLen; ++i) {
            int priority1 = getCharPriority(str1[i]);
            int priority2 = getCharPriority(str2[i]);
            
            if (priority1 != priority2) {
                return priority1 < priority2;
            }
        }
        
        return str1.length() < str2.length();
    }
}

#endif 