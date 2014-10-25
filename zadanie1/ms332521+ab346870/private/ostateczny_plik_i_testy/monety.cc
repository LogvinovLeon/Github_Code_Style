/*
    Program: monety.cc
    Authors: Adam Boniecki, Mateusz Siwiec
    Date: 16/10/2014
*/

#include <iostream>
#include <boost/regex.hpp>
#include <string>
#include <list>


using namespace std;


   // types used

    typedef list< pair<int,string> >           DescriptionList         ;
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

int first_year(DescriptionList& description_lines)
{
    DescriptionList::iterator iter = description_lines.begin();
    return (*iter).first;
}


int last_year(DescriptionList& description_lines)
{
    DescriptionList::iterator iter = description_lines.end();
    iter--;
    return (*iter).first;
}


void print_line(DescriptionList::iterator iter)
{
    cout << (*iter).second << " ";
    cout << (*iter).first << endl;
}


void print_list_in_range(DescriptionList& description_lines, int start, int end)
{
    DescriptionList::iterator iter;

    if(start < end)
    {
        iter = description_lines.begin();

        while(iter != description_lines.end() && (*iter).first < start)
        {
            iter++;
        }

        while(iter != description_lines.end() && (*iter).first >= start && (*iter).first < end)
        {
            print_line(iter);
            iter++;
        }
    }
    else if(end < start)
    {
        iter = description_lines.end();
        iter--;

        while(iter != description_lines.begin() && (*iter).first >= start)
        {
            iter--;
        }

        while(iter != description_lines.begin() && (*iter).first >= end && (*iter).first < start)
        {
            print_line(iter);
            iter--;
        }

        if(iter == description_lines.begin() && (*iter).first >= end && (*iter).first < start)
        {
            print_line(iter);
        }
    }
}

void print_all(DescriptionList& description_lines, int year1, int year2)
{

    // set proper interval

    if(year1 > last_year(description_lines))
        year1 = last_year(description_lines);
    else if(year1 < first_year(description_lines))
        year1 = first_year(description_lines);


    if(year2 > last_year(description_lines))
        year2 = last_year(description_lines) + 1;
    else if(year2 < first_year(description_lines))
        year2 = first_year(description_lines);

    // print sorted lines

    print_list_in_range(description_lines, first_year(description_lines), year1);

    if(year1 < year2)
        print_list_in_range(description_lines, year2, year1);

    print_list_in_range(description_lines, year2, last_year(description_lines) + 1);
}

int main()
{

    // variables used

    bool                                       read_lines = true                      ;
    int                                       line_number = 0                         ;
    string*                                          line = new string                ;
    int                                             year1 = 0                         ;
    int                                             year2 = 0                         ;
    string*                                   description = new string                ;
    DescriptionList                     description_lines                             ;

    // main program

    while(read_lines) // read input
    {
        line_number++;

        if(getline(cin, *line))
        {

            switch(check_line(*line, year1, year2, *description)) // match line pattern and set values of year1, year2 and *description
            {
                case DESCRIPTION :
                        description_lines.push_back( make_pair(year2, *description) ); // add line to description_lines list
                break;

                case INCORRECT_LINE :
                    report_error(line_number, *line);
                break;

                case PROPER_CLOSING_LINE : // stop reading
                    read_lines = false;
                break;

                case IMPROPER_CLOSING_LINE : // stop reading
                    read_lines = false;
                    report_error(line_number, *line);
                break;
            }
        }
        else // there was no closing line
        {
            report_error(line_number, "");

            delete description;
            delete line;

            return 0;
        }

    }

    // ignore all lines after PROPER_CLOSING_LINE or IMPROPER_CLOSING_LINE

    while(getline(cin, *line))
    {
        line_number++;
        report_error(line_number, *line);
    }

    // sort and print list

    description_lines.sort();
    print_all(description_lines, year1, year2);

    delete description;
    delete line;

    return 0;
}
