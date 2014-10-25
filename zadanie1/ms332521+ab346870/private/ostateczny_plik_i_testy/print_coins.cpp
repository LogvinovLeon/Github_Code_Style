#include <string>
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

typedef list<pair<int, string> > DescriptionList;
typedef DescriptionList::const_iterator DLIterator; //TODO nazwy ewentualnie mozna zmienic
typedef reverse_iterator<DLIterator> RevIterator;

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
    // TODO chyba można by też dać zamiast compa taką lambdę:
    // [](pair<int, string> p, int val) -> bool { return p.first < val; }
    DLIterator year1_ite = lower_bound(l.begin(), l.end(), year1, comp);
    DLIterator year2_ite = lower_bound(l.begin(), l.end(), year2, comp);

    for_each(l.cbegin(), year1_ite, print_line);

    if (year1 < year2)
        for_each(RevIterator(year2_ite), RevIterator(year1_ite), print_line);

    for_each(year2_ite, l.cend(), print_line);
}

int main()
{
    DescriptionList l;

    //tworzymy listę [0, 2, ..., 38] na potrzeby testowania
    for(int i = 0; i < 40; i += 2)
        l.push_back(make_pair(i, string()));

    l.sort();

    int year1, year2;

    cin >> year1;
    cin >> year2;

    print_pairs(l, year1, year2);

    return 0;
}
