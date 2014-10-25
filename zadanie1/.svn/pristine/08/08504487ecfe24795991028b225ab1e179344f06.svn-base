#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

// obsluguje liczby od -9 999 999 999 do 9 999 999 999
// czyli zawiera cały zakres int32
// linii na wejsciu moze byc int64
// bez plusow z przodu


typedef pair<long long, string> moneta;

bool przetworzMonete(const string& wejscie, long long& data, string& opis)
{
    string liczba("(-?[1-9][0-9]{0,9})");
    
    regex wpis("^([\\S].*?)(?:\\s+)" + liczba + "(\\s*)");

    smatch dopasowanie;

    if (!regex_match(wejscie, dopasowanie, wpis))
        return false;

   // cout << dopasowanie[0] << "         " << dopasowanie[1] << "         " << dopasowanie[2] << endl;
    data = stoll(dopasowanie[2]);
    opis = dopasowanie[1];
    
    return true;
}
bool przetworzOstatnia(const string & wejscie, long long& r1, long long& r2)
{
    string liczba("(-?[1-9][0-9]{0,9})");
    
    regex ostatniaLinia(liczba + "\\s+" + liczba + "\\s*");
    
    smatch dopasowanie;
    
    if (!regex_match(wejscie, dopasowanie, ostatniaLinia))
        return false;
    
 //   cout << dopasowanie[0] << "         " << dopasowanie[1] << "         " << dopasowanie[2] << endl;
    r1 = stoll(dopasowanie[1]);
    r2 = stoll(dopasowanie[2]);
    
    return true;
}

void zglosBlad(const unsigned long long& nr, const string& opis)
{
    cout << "Error in line " << nr << ":" << opis << endl;
}

bool czytaj(vector<moneta>& dane, long long& r1, long long& r2)
{
    string wejscie;
    string opis;
    long long data;

    cmatch tekst;

    unsigned long long numer = 0;

    while (getline(cin, wejscie))
    {
//        cout << numer << endl;
        numer++;
        if (przetworzOstatnia(wejscie, r1, r2))
        {
            cout << "ostatnia" << endl;
            break;
        }
        else if (przetworzMonete(wejscie, data,  opis))
        {
            cout << "moneta" << endl;
            dane.push_back(make_pair(data, opis));
        }
        else
            zglosBlad(numer, wejscie); 
    }
    while (getline(cin, wejscie))
    {
        numer++;
        zglosBlad(numer, wejscie);
    }
}


int main()
{
    vector<moneta> dane;
    long long r1, r2;
    
    if (czytaj(dane, r1, r2))
    {
 //       for (int i = 0; i < dane.size(); i++)
   //         cout << dane[i].first << " " << dane[i].second << endl;
        cout << r1 << " " << r2 << endl;
        // sortowanie
    }
    return 0;
}

