// kompiluje poleceniem z Makefile

#include <stdio.h>
#include <string>
#include <boost/regex.hpp>

using namespace boost;
using namespace std;


int main()
{
    // deklaracja zmiennych
    int const     n = 1000;
    string      str ;
    regex   pattern ("(\\S.*?)\\s+(-?[1-9]\\d*)\\s*");
    smatch       sm ;
    
    bool*     match = new   bool[n];
    int*       year = new    int[n];
    string*   descr = new string[n];
    int           i = 0;
    int        a, b ;
    

    // wczytanie inputu

    while (getline(cin, str))
    {
        
        if (regex_match(str, sm, pattern))
        {
            descr[i] = sm[1];
            match[i] = true;
            // year[i] = ???

            cout << ">>> " << sm[1] << " " << sm[2] << endl;
            // do zrobienia: ogarniczenie zakresu dat, przerzucenie na ich int i wpisywanie do tablic year[], descr[] rozpoznanie ostatniego wiersza
        }
	    else
        {
            match[i] = false;
		    descr[i] = str; // jak wiersz jest niepoprawny w calosci jest przechowany w descr[i]
                            // a year[i] zostawiamy nieokreslone
            cout << ">>> try again" << endl;
        }


        i++;
    }
    //teraz mamy wczytane i wierszy, wypelnione tablice bool i sm[i] i teraz beda wszystkie sortowania itp
    return 0;
}
