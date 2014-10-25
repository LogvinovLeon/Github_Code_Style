// compilation: g++ $< -std=c++11 -lboost_regex -o $@
// g++ 4.8.2
// author: Krzysztof Stanislawek    ks347253@students.mimuw.edu.pl

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <algorithm>
#include <string>

// supported years: [-999'999'999, 999'999'999] \ {0}
typedef int32_t                      Year;
typedef std::pair<std::string, Year> CoinRecord;
enum class LineType : std::int8_t 
{
    COIN, 
    CLOSING, 
    BAD 
};

void signal_error(int nr, std::string line = "")
{
    std::cerr << "Error in line " << nr << ":" << line << std::endl;
}

bool does_match(const std::string &line, const boost::regex &regex)
{
    return boost::regex_match(line.c_str(), regex);
}

bool does_match(const std::string &line, const boost::regex &regex, 
    boost::cmatch &matches)
{
    return boost::regex_match(line.c_str(), matches, regex);
}

LineType classify_line(const std::string &line, boost::cmatch &matches)
{
    static const std::string DESCR = "(\\S.*\\S|\\S)";
    static const std::string YEAR = "(-?[1-9][0-9]{0,8})"; 
    static const std::string NUM = "-?[0-9]+";
    static const std::string SPC = "\\s+";
    static const std::string SPC_OPTIONAL = "\\s*";

    static const boost::regex COIN_REGEX(DESCR + SPC + YEAR + SPC_OPTIONAL);
    static const boost::regex VERIFY_CLOSING_REGEX(YEAR + SPC + YEAR + 
        SPC_OPTIONAL);
    static const boost::regex CLASSIFY_CLOSING_REGEX(NUM + SPC + NUM + 
        SPC_OPTIONAL);

    if (does_match(line, CLASSIFY_CLOSING_REGEX))
    {
        if (does_match(line, VERIFY_CLOSING_REGEX, matches))
            return LineType::CLOSING;
        else
            return LineType::BAD;
    }
    else 
    {
        if (does_match(line, COIN_REGEX, matches))
            return LineType::COIN;
        else
            return LineType::BAD;
    }
}

template<typename MatchType>
std::string match_to_str(const MatchType &match)
{
    return std::string(match.first, match.second);
}

template<typename MatchType>
Year match_to_year(const MatchType &match)
{
    return boost::lexical_cast<Year>(match_to_str(match));
}

bool parse_records(std::vector<CoinRecord> &coins, Year &r1, Year &r2)
{
    boost::cmatch matches;
    std::string line;

    size_t nr = 1;
    bool closed = false;
    while (std::getline(std::cin, line))
    {
        LineType type;
        if (closed)
            type = LineType::BAD;
        else
            type = classify_line(line, matches);

        switch (type)
        {
            case LineType::COIN:
                coins.push_back(CoinRecord{match_to_str(matches[1]), 
                                           match_to_year(matches[2])});
                break;
            case LineType::CLOSING:
                closed = true;
                r1 = match_to_year(matches[1]);
                r2 = match_to_year(matches[2]);
                if (r1 >= r2)
                    signal_error(nr, line);
                break;
            case LineType::BAD:
                signal_error(nr, line);
                break;
        }
        nr++;
    }
    
    if (!closed)
    {
        signal_error(nr);
        return false;
    }
    return true;
}

bool coin_comparator(const CoinRecord &l, const CoinRecord &r)
{
    if (l.second != r.second)
        return l.second < r.second;
    else
        return l.first < r.first;
}

bool coin_year_comparator(const CoinRecord &l, const Year &r)
{
    return l.second < r;
}

std::vector<CoinRecord>::iterator findRecord(std::vector<CoinRecord> &coins,
    Year year)
{
    return std::lower_bound(coins.begin(), coins.end(), year, 
        coin_year_comparator);
}

void sort_coins(std::vector<CoinRecord> &coins, const Year &r1,
    const Year &r2)
{
    std::sort(coins.begin(), coins.end(), coin_comparator);
    auto r1It = findRecord(coins, r1),
         r2It = findRecord(coins, r2);

    if (r1 < r2)
    {
        std::reverse(r1It, r2It);
    }
    else if (r1 > r2)
    {
        int idxR1 = r1It - coins.begin(), idxR2 = r2It - coins.begin();
        coins.resize(coins.size() + (idxR1 - idxR2));

        // iterators are possibly broken now
        for (int idx = signed(coins.size()) - 1; idx >= idxR1; idx--)
            coins.at(idx) = coins.at(idx - (idxR1 - idxR2));
    }
}

void setup_ios()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.exceptions(std::istream::badbit);
}

signed main()
{
    setup_ios();

    std::vector<CoinRecord> coinRecords;
    Year r1, r2;
    if (parse_records(coinRecords, r1, r2))
    {
        sort_coins(coinRecords, r1, r2);
        for (CoinRecord &record : coinRecords)
            std::cout << record.first << " " << record.second << std::endl;
    }
}
