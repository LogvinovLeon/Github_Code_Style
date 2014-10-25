#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

// obsluguje liczby od -9 999 999 999 do 9 999 999 999
// czyli zawiera cały zakres int32
// linii na wejsciu moze byc int64
// bez plusow z przodu

// <opis, rok>
typedef pair<string, long long> moneta;

static const string liczba("(-?[1-9][0-9]{0,9})");


static void wypiszMonete(moneta m)
{
    cout << m.first << ' ' << m.second << endl;
}

static bool porownajMonety(const moneta& a, const moneta& b)
{
    if (a.second != b.second)
        return a.second < b.second;
    else
        return a.first < b.first;
}

static void wypisz(vector<moneta>& monety, const long long& r1, const long long& r2)
{
    if(monety.empty())  //DIF empty
        return;
    // "" jest leksykograficznie najmniejszym ciągiem znaków
    // pierwsza moneta wybita w roku >= r1
    auto poczatekR1 = lower_bound(monety.begin(), monety.end(),
            make_pair("", r1), porownajMonety);

    for (auto i = monety.begin(); i < poczatekR1; i++)
        wypiszMonete(*i);

    // pierwsza moneta wybita w roku >= r2
    auto poczatekR2 = lower_bound(poczatekR1, monety.end(),
            make_pair("", r2), porownajMonety);

    for (auto i = poczatekR2 - 1; i >= poczatekR1; i--)
        wypiszMonete(*i);
    
    for (auto i = poczatekR2; i < monety.end(); i++)
        wypiszMonete(*i);
}

static bool przetworzMonete(const string& wejscie, long long& data, string& opis)
{
    static const regex wpis("^([\\S].*?)(?:\\s+)" + liczba + "(\\s*)");

    smatch dopasowanie;

    if (!regex_match(wejscie, dopasowanie, wpis))
        return false;

    data = stoll(dopasowanie[2]);
    opis = dopasowanie[1];

    if(opis == "0") //DIF r0
        return false;

    return true;
}

static bool przetworzOstatnia(const string& wejscie, long long& r1, long long& r2)
{
    static const regex ostatniaLinia(liczba + "\\s+" + liczba + "\\s*");

    smatch dopasowanie;

    if (!regex_match(wejscie, dopasowanie, ostatniaLinia))
        return false;

    r1 = stoll(dopasowanie[1]);
    r2 = stoll(dopasowanie[2]);

    if(r1 == 0 || r2 == 0 || r1 > r2)  //DIF r0, ord
        return false;

    return true;
}

static void zglosBlad(const unsigned long long& nr, const string& opis)
{
    cerr << "Error in line " << nr << ":" << opis << endl;
}

static bool czytaj(vector<moneta>& dane, long long& r1, long long& r2)
{
    string wejscie;
    string opis;
    long long data;

    cmatch tekst;

    unsigned long long numer = 0;
    bool koniec = false;

    while (getline(cin, wejscie))
    {
        numer++;
        if (przetworzOstatnia(wejscie, r1, r2))
        {
            koniec = true;
            break;
        }
        else if (przetworzMonete(wejscie, data,  opis))
        {
            dane.push_back(make_pair(opis, data));
        }
        else
            zglosBlad(numer, wejscie); 
    }
    while (getline(cin, wejscie))
    {
        numer++;
        zglosBlad(numer, wejscie);
    }
    if (!koniec)
    {
        zglosBlad(numer + 1, "");
        return false;
    }
    return true;
}


int main()
{
    vector<moneta> dane;
    long long r1, r2;

    if (czytaj(dane, r1, r2))
    {
        sort(dane.begin(), dane.end(), porownajMonety);
        wypisz(dane, r1, r2);
    }
    return 0;
}
