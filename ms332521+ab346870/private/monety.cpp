#include <iostream>
#include <boost/regex.hpp>
#include <string>
#include <list>


using namespace std;


   // types used
    
    typedef list< pair<int,string> >    	   DescriptionList         ; 
	enum LineType { DESCRIPTION,
                INCORRECT_LINE,
                PROPER_CLOSING_LINE,
                IMPROPER_CLOSING_LINE };




// functions used

LineType check_line(const string& line, int& year1, int& year2, string& description)
{
    boost::regex line_expr ("([!-~].*?)\\s+(-?[1-9]\\d{0,4})\\s*");
    boost::smatch line_match;

    if (boost::regex_match(line, line_match, line_expr))
    {
        year2 = stoi(line_match[2]);

        boost::regex digits_expr ("(-?[1-9]\\d*)");
        boost::smatch digits_match;

        //zamiast nowej zmiennej można od razu nadpisać string description, ale w tym momencie jeszcze nie wiadomo, czy to poprawny opis
        string first_group = line_match[1]; //z jakiegoś powodu nie mogę podać bezpośrednio line_match[1] jako argument do regex_match

        if (boost::regex_match(first_group, digits_match, digits_expr))
        {
            string digits_str = digits_match[1];
            int len = digits_str.length();

            if (len > 6 || (len == 6 && digits_str[0] != '-'))
                return /*LineType::*/INCORRECT_LINE;

            year1 = stoi(digits_match[1]);

            if(year1 >= year2)
                return /*LineType::*/IMPROPER_CLOSING_LINE;
            else
                return /*LineType::*/PROPER_CLOSING_LINE;
        }
        else
        {
            description = first_group;
            return /*LineType::*/DESCRIPTION;
        }
    }
    else
    {
        return /*LineType::*/INCORRECT_LINE;
    }
}

/*
void add_to_list(DescriptionList& description_lines)
{
					
}

*/
void print_list(DescriptionList description_lines, int interval_start, int interval_end)
{
	
	DescriptionList::iterator  description_lines_iterator = description_lines.begin();
	DescriptionList::iterator interval_start_iterator;
	DescriptionList::iterator interval_end_interator;
	
	
	
	while(description_lines_iterator != description_lines.end())
	{
		 cout << (*description_lines_iterator).second << " "
			  << (*description_lines_iterator).first << endl;
		
		description_lines_iterator++;
		
	}
	
	
}






int main()
{
    
    

    
    
    // variables used
    
    bool                                       read_lines = true                      ;
    int                                       line_number = 0                         ;
    string                                          *line = new string                ;
    int                                             year1 = 0                         ;
    int                                             year2 = 0                         ;
    string                                   *description = new string                ;
    DescriptionList                     description_lines                             ;
    int                                    interval_start                             ;
    int                                      interval_end                             ;
    
    // main program
    
    while(read_lines)
    {
		line_number++;
		
        if(getline(cin, *line))
        {
            switch(check_line(*line, year1, year2, *description))
			{	
				case        DESCRIPTION :
					cout << ">>> DESCRIPTION" << endl;
					description_lines.push_back( make_pair(year2, *description) );
					
					
				break;
				
				
				case      INCORRECT_LINE :
					cout << ">>> INCORRECT_LINE" << endl;
					//cerr << "Error in line " << line_number << ":"  << *line << endl;
					
					
				break;
				
				
				case       PROPER_CLOSING_LINE :
					
					cout << ">>> PROPOER_CLOSING_LINE" << endl;
					read_lines     = false;	
					interval_start = year1;
					interval_end   = year2;	
					
					
				break;
				
				
				case     IMPROPER_CLOSING_LINE :
					cout << ">>> IMPROPOER_CLOSING_LINE" << endl;
					read_lines     = false;
					
					//cerr << "Error in line " << line_number << ":"  << *line << endl;
					
					
				break;
			}
        }
        else // there is no closing_line
        {
            read_lines = false;
            cout << ">>> BRAK WIERSZA KONCOWEGO" << endl;
            //cerr << "Error in line " << line_number << ":" << endl;
        }
        
    }
    // we have reached PROPER_CLOSING LINE, IMPROPER_CLOSING_LINE or there is no closing line
    // all other lines will be ignored
    
    while(getline(cin, *line))
    {
		line_number++;
		cout << ">>> JUZ WCZYTALISMY WIERSZ KONCOWY" << endl;
		//cerr << "Error in line " << line_number << ":"  << *line << endl;
	}
    
    
    
    
	description_lines.sort();
    
    print_list(description_lines, interval_start, interval_end);
    
    
    return 0;
}
