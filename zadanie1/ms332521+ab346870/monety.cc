#include <iostream>
#include <boost/regex.hpp>
#include <string>
#include <list>
#include <algorithm>


using namespace std;


// types used

typedef list< pair<int,string> >           DescriptionList         ;
typedef DescriptionList::const_iterator         DLIterator         ;
typedef reverse_iterator<DLIterator>           RevIterator         ;

enum LineType { DESCRIPTION,
                INCORRECT_LINE,
                PROPER_CLOSING_LINE,
                IMPROPER_CLOSING_LINE };


// functions used

void report_error(int line_number, const string& line)
{
    cerr << "Error in line " << line_number << ":"  << line << endl;
}

LineType check_line(const string& line, int& year1, int& year2, string& description)
{
    boost::regex line_expr ("([!-~].*?)\\s+(-?[1-9]\\d{0,4})\\s*");
    boost::smatch line_match;

    if (boost::regex_match(line, line_match, line_expr))
    {
        year2 = stoi(line_match[2]);

        boost::regex digits_expr ("(-?[1-9]\\d*)");
        boost::smatch digits_match;

        string first_group = line_match[1];

        if (boost::regex_match(first_group, digits_match, digits_expr))
        {
            string digits_str = digits_match[1];
            int len = digits_str.length();

            if (len > 6 || (len == 6 && digits_str[0] != '-'))
                return INCORRECT_LINE;

            year1 = stoi(digits_match[1]);

            if(year1 >= year2)
                return IMPROPER_CLOSING_LINE;
            else
                return PROPER_CLOSING_LINE;
        }
        else
        {
            if (first_group == "0" || first_group == "-0")
                return INCORRECT_LINE;
            else
            {
                description = first_group;
                return DESCRIPTION;
            }
        }
    }
    else
    {
        return INCORRECT_LINE;
    }
}

// To be used with std::lower_bound
bool comp(pair<int, string> p, int val)
{
    return p.first < val;
}

void print_line(pair<int, string> p)
{
    cout << p.second << " " << p.first << endl;
}

/*
 * Prints all pairs p in l for which p.first < year1 in increasing order,
 * then all for which year1 <= p.first < year2 in decreasing order,
 * followed by those, that satisfy p.first >= year2 in increasing order.
 *
 * Assumes l is a sorted.
 */
void print_pairs(DescriptionList& l, int year1, int year2)
{
    DLIterator year1_ite = lower_bound(l.begin(), l.end(), year1, comp);
    DLIterator year2_ite = lower_bound(l.begin(), l.end(), year2, comp);

    for_each(l.cbegin(), year1_ite, print_line);

    if (year1 < year2)
        for_each(RevIterator(year2_ite), RevIterator(year1_ite), print_line);

    for_each(year2_ite, l.cend(), print_line);
}


int main()
{

    // variables used

    bool                                   read_lines = true                  ;
    int                                   line_number = 0                     ;
    int                                         year1 = 0                     ;
    int                                         year2 = 0                     ;
    string*                                      line = new string            ;
    string*                               description = new string            ;
    DescriptionList                 description_lines                         ;

    // main program

    while(read_lines)
    {
        line_number++;

        if(getline(cin, *line))
        {

            switch(check_line(*line, year1, year2, *description))
            {
                case        DESCRIPTION :
                    description_lines.push_back(make_pair(year2, *description));
                break;

                case      INCORRECT_LINE :
                    report_error(line_number, *line);
                break;

                case       PROPER_CLOSING_LINE :
                    read_lines = false;
                break;

                case     IMPROPER_CLOSING_LINE :
                    read_lines = false;
                    report_error(line_number, *line);
                break;
            }
        }
        else
        {
            report_error(line_number, "");

            delete description;
            delete line;

            return 0;
        }

    }


    while(getline(cin, *line))
    {
        line_number++;
        report_error(line_number, *line);
    }


    description_lines.sort();

    print_pairs(description_lines, year1, year2);

    delete line;
    delete description;

    return 0;
}
