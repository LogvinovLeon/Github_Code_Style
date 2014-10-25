/*
	Program monety v1
	@Autorzy: Jakub Królak, Bartosz Michalak
*/
#include<iostream>
#include<vector>
#include<utility>
#include<string>
#include<boost/regex.hpp>
/*
	kompilowane w g++ z opcjami -Wall -O2 -std=c++11 -lboost_regex
	zalozenia projektowe:
		- zakres liczb obslugiwany przez program: -999 999 999 - 1 999 999 999
		- zera wiodace sa OK dopoki zapis calej liczby nie przekracza 10 znakow
*/
using namespace std;

typedef pair<string, int> moneta;
typedef vector<moneta> lista_monet;

static void wypisz_monete(const lista_monet &historia, int i) {
	cout << historia[i].first << " " << historia[i].second << endl;
}

static bool pairCompare(const moneta& firstElem, const moneta& secondElem) {
	if (firstElem.second != secondElem.second)
		return firstElem.second < secondElem.second;
	else
		return firstElem.first < secondElem.first;
}

static void sort_i_wypisz_liste(lista_monet &historia, int rok1, int rok2) {
	if (!historia.empty()) {
		sort(historia.begin(), historia.end(),pairCompare);
		size_t i = 0, indeks_rok1 = 0, indeks_rok2 = 0;
		bool if_r2_set = false;
		
		if (rok1 < rok2) {
			while (i < historia.size() && historia[i].second < rok1) {
				wypisz_monete(historia, i);
				i++;
			}
			indeks_rok1 = i;
			while (i < historia.size() && historia[i].second < rok2) {
				i++;
			}
			indeks_rok2 = i;
			if (indeks_rok2 > 0) {
				for (i = indeks_rok2 - 1; i > indeks_rok1; i--)
					wypisz_monete(historia, i);
				if (indeks_rok1 < historia.size() && indeks_rok1 != indeks_rok2) { // to trzeba sprawdzic, bo indeks_rok1 moze byc rowny historia.size() lub indeks_rok2
					wypisz_monete(historia, indeks_rok1);
				}
			}
			for (i = indeks_rok2; i < historia.size(); i++)
				wypisz_monete(historia, i);
		} else {
			
			while (i < historia.size() && historia[i].second < rok1) {
				wypisz_monete(historia, i);
				if (historia[i].second >= rok2 && !if_r2_set) {
					indeks_rok2 = i;
					if_r2_set = true;
				}
				i++;
			}
			if (!if_r2_set) { // jezeli rok2 == rok1
				indeks_rok2 = i;
			}
			for (i = indeks_rok2; i < historia.size(); i++)
				wypisz_monete(historia, i);
		}
	}
}

static moneta stworz_monete(string opis, int rok) {
	moneta m(opis, rok);
	return m;
}

static void dodaj_monete(lista_monet &lista, moneta &m) {
	lista.push_back(m);
}

static void wypisz_blad(long wiersz, string tresc_linijki) {
	cerr << "Error in line " << wiersz << ":" << tresc_linijki << endl;
}

static bool jest_w_zakresie(string napis_liczbowy) {
	const int max_length = 10;
	return (napis_liczbowy.length() < max_length)
		   || ( (napis_liczbowy.length() == max_length) && (napis_liczbowy[0] == '-' || napis_liczbowy[0] == '1' || napis_liczbowy[0] == '0') );
}

static void przetworz_wejscie() {
	lista_monet historia;
	long wiersz = 1;
	bool koniec = false;
	string wejscie;
	boost::regex wzorzec_monety("(\\S.*\\S|\\S)(\\s+)(-?\\d+)(\\s*)");
	boost::regex wzorzec_koncowy("(-?\\d+)(\\s+)(-?\\d+)(\\s*)");
	boost::smatch wynik;
	int rok1, rok2;
	moneta m;
	while(getline(cin, wejscie)) {
		if (koniec) {
			wypisz_blad(wiersz, wejscie);
		} else 
			if (regex_match(wejscie, wynik, wzorzec_koncowy)) {
				rok1 = jest_w_zakresie(wynik[1]) ? stoi(wynik[1]) : 0;
				rok2 = jest_w_zakresie(wynik[3]) ? stoi(wynik[3]) : 0;
				if (rok1 != 0 && rok2 != 0) {
					if (rok1 >= rok2) {
						//zgodnie ze specyfikacja taki wiersz jest bledem,
						//ALE rowniez jest tez wierszem koncowym i wypisujemy wszystko
						wypisz_blad(wiersz, wejscie); 
					}
					koniec = true;
					sort_i_wypisz_liste(historia, rok1, rok2);
				} else {
					//wiersz z chocby jednym zerem jest bledny
					//i nie traktujemy go jako konca wejscia
					wypisz_blad(wiersz, wejscie);
				}
			} else {
				if (regex_match(wejscie, wynik, wzorzec_monety)) { //jesli linijka jest poprawnie sformatowana, dorzucamy nowa monete
					rok1 = jest_w_zakresie(wynik[3]) ? stoi(wynik[3]) : 0;
					if (rok1 != 0) {
						m = stworz_monete(wynik[1], rok1);
						dodaj_monete(historia, m);
					} else {
						wypisz_blad(wiersz, wejscie);
					}
				} else {
					wypisz_blad(wiersz, wejscie);
				}
		}
		wiersz++;
	}
	if(!koniec) {
		wypisz_blad(wiersz, "");
	}
}

int main() {
	przetworz_wejscie();
	return 0;
}

