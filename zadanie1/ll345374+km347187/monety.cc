#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <vector>
#include <utility>

using namespace std;
using namespace boost;

typedef pair<int32_t, string> tCoin;

static const string NUMBER(R"((-?[1-9]\d{0,8}))");
static const string OUT_OF_RANGE(R"(((?:-?[1-9]\d{9,})|0))");

static void reportError(uint32_t line, const string& text = "")
{
    cerr << "Error in line " << line << ":" << text << endl;
}

static bool lastLine(const string& text, int32_t& year1, int32_t& year2)
{
    static const regex regexp(NUMBER + R"(\s+)" + NUMBER + R"(\s*)");
    smatch match;

    if(!regex_match(text, match, regexp))
        return false;

    year1 = stoi(match[1].str());
    year2 = stoi(match[2].str());
    return true;
}

static bool parseRecord(const string& text, string& description, int32_t& year)
{
    static const regex regexpErr(OUT_OF_RANGE + R"(\s+)" + NUMBER + R"(\s*)");
    static const regex regexp(R"(^([^\s].*?)(?:\s+)" + NUMBER + R"(\s*))");
    smatch match;

    if(regex_match(text, match, regexpErr))
        return false;

    if(!regex_match(text, match, regexp))
        return false;

    description = match[1].str();
    year = stoi(match[2].str());
    return true;
}

static bool readInput(vector<tCoin>& coins, int32_t& year1, int32_t& year2)
{
    string text, description;
    int32_t year;
    bool lastLineOccured = false;
    uint32_t line = 1;

    while(!lastLineOccured && getline(cin, text)) {
        if(lastLine(text, year1, year2)) {
            lastLineOccured = true;

            if(year1 >= year2)
                reportError(line, "Blad w ostatniej linii.");
        } else if(parseRecord(text, description, year)) {
            tCoin coin(year, description);
            coins.push_back(coin);
        } else {
            reportError(line, text);
        }

        line++;
    }

    while(getline(cin, text)) {
        reportError(line, text);
        line++;
    }

    if(!lastLineOccured) {
        reportError(line);
        return false;
    }

    return true;
}

static void reorder(vector<tCoin>& coins, int32_t year1, int32_t year2)
{
    sort(coins.begin(), coins.end());
    auto left = lower_bound(coins.begin(), coins.end(), make_pair(year1, string("")));
    auto right = lower_bound(coins.begin(), coins.end(), make_pair(year2, string("")));
    reverse(left, right);
}

int main()
{
    vector<tCoin> coins;
    int32_t year1, year2;

    if(readInput(coins, year1, year2)) {
        reorder(coins, year1, year2);
        for(tCoin& coin : coins) {
            cout << coin.second << " " << coin.first << endl;
        }
    }

    return 0;
}
