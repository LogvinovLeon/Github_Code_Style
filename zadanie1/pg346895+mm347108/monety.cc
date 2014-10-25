// CXXFLAGS = -O2 -Wall -std=c++11 -lboost_regex

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdint>
#include <boost/regex.hpp>

using CoinData = std::pair<std::string, int>;
using EndData = std::pair<int, int>;

static const int MAX_YEAR = 1000 * 1000;

/*
 * returns true when there are two integers in string, no matter of their values
 * if integers are too big/small, 'endData' becomes {0, 0}
 */
static bool toEndLineData(const std::string &str, EndData &endData) {
    // regex: [whitespace]([digit])[whitespace]([digit])[whitespace]
    static const boost::regex twoIntsRegex(
        "^[[:blank:]]*"
        "([+-]?[[:digit:]]+)"
        "[[:blank:]]+"
        "([+-]?[[:digit:]]+)"
        "[[:blank:]]*$"
    );
    enum MatchIndex : std::uint8_t {
        firstInteger = 1,
        secondInteger = 2
    };
    
    boost::smatch what;
    if (!boost::regex_match(str, what, twoIntsRegex)) {
        return false;
    }
    
    endData = {0, 0};
    EndData result;
    
    try {
        result.first = std::stoi(what[MatchIndex::firstInteger]);
        result.second = std::stoi(what[MatchIndex::secondInteger]);
    } catch (...) {
        return true;
    }
    
    for (auto x : {result.first, result.second}) {
        if (x > MAX_YEAR || x < -MAX_YEAR) {
            return true;
        }
    }
    
    endData = std::move(result);
    return true;
}

/*
 * returns true when string fits to coin info format, no matter of year value
 * if year are too big/small, 'coinData' becomes {"", 0}
 */
static bool toCoinData(const std::string &str, CoinData &coinData) {
    // regex: [whitespace]([not whitespace][any symbols][not whitespace])[whitespace]([digits])[whitespace]
    static const boost::regex coinInfo(
        "^[[:blank:]]*"
        "([^[:blank:]].+[^[:blank:]])"
        "[[:blank:]]+"
        "([+-]?[[:digit:]]+)"
        "[[:blank:]]*$"
    );
    enum MatchIndex : std::uint8_t {
        name = 1,
        year = 2
    };
    
    boost::smatch what;
    if (!boost::regex_match(str, what, coinInfo)) {
        return false;
    }
    
    coinData = {"", 0};
    CoinData result;
    
    try {
        result.second = std::stoi(what[MatchIndex::year]);
    } catch (...) {
        return true;
    }
    result.first = what[MatchIndex::name];
    
    coinData = std::move(result);
    return true;
}

inline static void printError(size_t line, const std::string &str = "") {
    std::cerr << "Error in line " << line << ":" << str << std::endl;
}

static bool compareCoins(const CoinData &a, const CoinData &b, const int r1, const int r2) {
    if (r1 <= a.second && a.second <= r2 - 1 && r1 <= b.second && b.second <= r2 - 1) {
        if (a.second == b.second) {
            return a.first > b.first;
        } else {
            return a.second > b.second;
        }
    } else {
        if (a.second == b.second) {
            return a.first < b.first;
        } else {
            return a.second < b.second;
        }
    }
}

static void sortCoins(std::vector<CoinData> &coinsVec, const EndData &accordingTo) {
    auto comparator = [accordingTo](const CoinData &a, const CoinData &b)->bool {
        return compareCoins(a, b, accordingTo.first, accordingTo.second);
    };
    
    std::sort(coinsVec.begin(), coinsVec.end(), comparator);
}

static void printCoins(const std::vector<CoinData> &coins, const EndData &dataForPrint, std::ostream &out = std::cout) {
    // Either:
    // a) if (r1 < r2) iterator to first coin which date is greater than r1
    // b) if (r1 >= r2) iterator to first coin which date is equal or greater than r2
    auto secondPartBegin = coins.end();
    
    for (auto it = coins.begin(); it != coins.end(); ++it) {
        if (it->second >= dataForPrint.second && secondPartBegin == coins.end()) {
            secondPartBegin = it;
        }
        if (it->second >= dataForPrint.first) {
            if (secondPartBegin == coins.end()) {
                secondPartBegin = it;
            }
            break;
        }
        out << it->first << " " << it->second << std::endl;
    }
    
    for (auto it = secondPartBegin; it != coins.end(); ++it) {
        out << it->first << " " << it->second << std::endl;
    }
}

/*
 * checks correctness of end data
 * 'err' is true if we need to print error
 */
static bool checkEndData(const EndData &endData, bool &err) {
    err = false;
    
    if (!endData.first || !endData.second) {
        err = true;
        return false;
    }
    
    if (endData.first >= endData.second) {
        err = true;
    }
    
    return true;
}

int main() {
    std::vector<CoinData> coins;
    EndData dataForSort;
    
    size_t lastLineNumberRead = 0;
    bool reachedEnd = false;
    
    while (!std::cin.eof()) {
        std::string inputLine;
        std::getline(std::cin, inputLine);
        lastLineNumberRead++;
        
        if (reachedEnd) {
            printError(lastLineNumberRead, inputLine);
            continue;
        }
        
        if (toEndLineData(inputLine, dataForSort)) {
            bool printErr;
            if (checkEndData(dataForSort, printErr)) {
                reachedEnd = true;
            }
            if (printErr) {
                printError(lastLineNumberRead, inputLine);
            }
            
            continue;
        }
        
        CoinData lineData;
        if (toCoinData(inputLine, lineData)) {
            if (lineData.second) {
                coins.push_back(std::move(lineData));
            } else {
                printError(lastLineNumberRead, inputLine);
            }
            
            continue;
        }
        
        printError(lastLineNumberRead, inputLine);
    }
    
    if (reachedEnd) {
        sortCoins(coins, dataForSort);
        printCoins(coins, dataForSort);
    } else {
        printError(lastLineNumberRead + 1);
    }
    
    return 0;
    
}