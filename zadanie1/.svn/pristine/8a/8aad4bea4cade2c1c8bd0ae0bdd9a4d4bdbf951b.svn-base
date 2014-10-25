#include <string>
#include <boost/regex.hpp>
#include <list>

// do kompilowania poleceniem
//               make -f Makefile_readlines2
// to wywala plik wykonywalny
//               readlines2
// do testow tego pliku napisalem skrypcik
//               ./test_read_lines2
// ktory bierze dane z read_lines2.in i wywala do read_lines2.out




using namespace std;

//TODO jako że nie znam c++ to nie wiem czy tu nie powinno być jeszcze jakiegoś kwalifikatora, np. static...
		// moim zadniem tutaj nic nie trzeba wiecej. tak jak ponizej jest chyba ok (switch dziala)
enum LineType { CORRECT_DESCRIPTION,
                INCORRECT_DESCRIPTION,
                CORRECT_CLOSING_LINE,
                INCORRECT_CLOSING_LINE }; // tutaj bez 'class' po 'enum', bo cos sie ze switchem wali

/*
 * Return enum LineType, that determines whether passed in line
 * matches correct coin description or closing line.
 *
 * If check_line detects a correct closing line,
 * i.e. line consisting of two years separated by whitespace
 * (and possibly followed by more whitespace),
 * it will set arguments year1 and year2 to appropriate values.
 * Similarly if proper coin description is found,
 * check_line will set year2 and description appropriately.
 *
 * Assume proper year is in range [-99999, 0) or (0, 99999]
 */
 
 
 // wydaje mi sie, ze "LineType::" przed kazdym elementem z enuma nie jest potrzebny
 // TODO moim zdaniem trzeba zmienic kazdy z tych warunkow przy ifach w check_line na osobną funkcję
 //          bool correct_coin_description(string line)
 //	         bool correct_closing_line(string line) itp.
 
 
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
                return /*LineType::*/INCORRECT_DESCRIPTION;

            year1 = stoi(digits_match[1]);
            // nie mozna tutaj zamiast
            
    //         return /*LineType::*/CLOSING_LINE;
            
            // napisac
            
			if(year1 >= year2)
				return /*LineType::*/INCORRECT_CLOSING_LINE;
			else
				return /*LineType::*/CORRECT_CLOSING_LINE;
   
    //        ?????
    // Ale jeżeli year1 >= year2 to trzeba traktować to jako poprawny wiersz końcowy (poza tym, że wypisujemy DODATKOWO komunikat o błędzie)
        }
        else
        {
            description = first_group;
            return /*LineType::*/CORRECT_DESCRIPTION;
        }
    }
    else
    {
        return /*LineType::*/INCORRECT_DESCRIPTION;
    }
}

int main()
{

    // deklaracja zmiennych
    string str;
    list<pair<int, string> > lines;
    int line_num = 1;
    int year1 {0}, year2 {0}; // inicjalizacja na zero, zeby nie bylo balaganu w testach
    string desc;
    
    
    
    while(getline(cin, str))
    {
		switch(check_line(str, year1, year2, desc))
		{
		case COIN_DESCRIPTION :
		cout << "'" << str << "'" << endl;
		cout << ">>> COIN_DESCRIPTION	" << year1 << "	|| " << year2 << "	|| " << desc << endl;
		break;
 		case CLOSING_LINE :
 		cout << "'" << str << "'" << endl;
 		cout << ">>> CLOSING_LINE		" << year1 << "	|| " << year2 << "	|| " << desc << endl;
 		
 		break;
 		case INCORRECT_LINE :
 		cout << "'" << str << "'" << endl;
 		cout << ">>> INCORRECT_LINE		" << year1 << "	|| " << year2 << "	|| " << desc << endl;
		
		break;
		}
	}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // read input
    // handle line
    // add to list
    // final line
    // new_error
    // sort_list
    // 
    
    
    
    
    
    
    
    /*
    
        
    
    // wczytanie inputu
    //TODO trzeba jakoś sprawdzić, czy w ogóle wczytaliśmy wiersz końcowy
    while (getline(cin, str))
    {
        if (regex_match(str, sm, pattern))
        {
            try
            {
                r2 = stoi(sm[2]);
                if (r2 == 0)
                    cerr << "Error in line " << line_num << ":"  << str << endl;
            }
            catch (out_of_range& e)
            {
                cerr << "Error in line " << line_num << ":"  << str << endl;
                continue;
            }

            try
            {
                r1 = stoi(sm[1]);
                if (r1 == 0) //TODO zakładam tutaj, że 0 nie jest poprawnym opisem, ale pewnie jest
                    cerr << "Error in line " << line_num << ":"  << str << endl;
            }
            catch (out_of_range& e)
            {
                cerr << "Error in line " << line_num << ":"  << str << endl;
            }
            catch (invalid_argument& e)
            {
                lines.push_back(make_pair(r2, sm[1]));
                cout << ">>> " << sm[1] << " " << r2 << endl; //TODO "sanity check", do usunięcia później
                continue;
            }

            //Jeśli jesteśmy w tym miejscu, to wczytaliśmy wiersz końcowy
            break;
        }
	    else
        {
            //TODO ta linijka się powtarza, pewnie lepiej zrobić z tego funkcję
            cerr << "Error in line " << line_num << ":"  << str << endl;
        }

        line_num++;
    }

    //TODO sortowi można zapodać funkcję porównującą sortowane elementy, żeby sortował wedle naszych potrzeb
    //choć chyba wystarczy zamienić pary (opis, rok) na pary (rok, opis), żeby posortował tak jak chcemy
    lines.sort();

    for (list<pair<int, string> >::const_iterator i = lines.begin(); i != lines.end(); i++)
        cout << (*i).second << " " << (*i).first << endl;
*/
    return 0;
}
