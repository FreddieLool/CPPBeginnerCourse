#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sstream>

class Utils {
public:
    static std::vector<std::string> splitString(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(s);
        std::string token;
        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

#endif // UTILS_H
