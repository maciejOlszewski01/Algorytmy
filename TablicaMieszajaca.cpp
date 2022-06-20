/*ALGO2 IS1 212B LAB07
Maciej Olszewski
om49360@zut.edu.pl
*/

#include <iostream>
#include <time.h>
#include <fstream>



class Element {
public:
	int klucz;

	Element(int a) {
		klucz = a;
	}
	Element() {
		klucz = (rand() % 20000) + 20000;
	}
};

class Hashing {
public:
	Element* tab = new Element[997];
	// 0 = podwojne 1 = liniowe 
	bool rodzajHashowania;


	void insert(int x) {
		//mieszanie podwojne
		Element a = Element(x); 
		int warPoHasz = hash(a.klucz);
		if (tab[warPoHasz].klucz <= 0) {
			tab[warPoHasz] = a;
		}
		else if(tab[warPoHasz].klucz == a.klucz) {
			std::cout << "\n Powtórzony klucz\n";
		}

		else if(rodzajHashowania == 0) {
			int temp = hash2(a.klucz);
			while (true) {
				if (tab[(warPoHasz + temp) % 997].klucz == a.klucz) {
					std::cout << "\n Powtórzony klucz\n";
					break;
				}
				if (tab[(warPoHasz+temp) % 997].klucz <= 0 ) {
					tab[(warPoHasz+ temp) % 997] = a;
					break;
				}
				temp += temp;
			}
		}
		//adresowanie liniowe
		else {
			int temp = 1;
			while (temp < 997) {
				if (tab[(warPoHasz + temp) % 997].klucz == a.klucz) {
					std::cout << "\n Powtórzony klucz\n";
					break;
				}

				if (tab[(warPoHasz + temp)%997].klucz <= 0) {
					tab[(warPoHasz + temp) % 997] = a;
					break;
				}
				temp += 1;
				if (temp == 997) {
					std::cout << "\n Brak Miejsca w tablicy\n";
				}
			}
		}

		


	}

	void insert_x(int x) {
		//mieszanie podwojne
		int temp = 0;
		int warPoHash;
		while (temp < x) {
		Element a = Element();
		warPoHash = hash(a.klucz);
		if (tab[warPoHash].klucz == a.klucz) {
			std::cout << "\n Powtórzenie klucza Klucz zast¹piono \n";
			continue;

		}
		if (tab[warPoHash].klucz <= 0) {
			
			tab[warPoHash] = a;
			temp++;
		}
		else if (rodzajHashowania == 0) {
			int temp2 = hash2(a.klucz);
			
			while (true) {
				warPoHash = (warPoHash + temp2) % 997;
				if (tab[warPoHash].klucz == a.klucz) {
					std::cout << "\n Powtórzenie klucza Klucz zast¹piono \n";
					break;

				}
				if (tab[warPoHash ].klucz <= 0) {
					
					tab[warPoHash] = a;
					temp++;
					break;
				}
				
			}
		}
		//adresowanie liniowe
		else {

			while (true) {
				warPoHash += 1;
				warPoHash = warPoHash % 997;
				if (tab[warPoHash].klucz == a.klucz) {
					std::cout << "\n Powtórzenie klucza Klucz zast¹piono \n";
					break;
				}
				if (tab[warPoHash].klucz <= 0) {
					
					tab[warPoHash] = a;
					temp++;
					break;
				}
				
			}
		}
	}

	}

	void wyswietl(int a, int b) {
		while (a <= b) {
			std::cout << " Pozycja: " << a << " Wartosc klucza " << tab[a].klucz << "\n";
			a++;
		}
	}

	int find(int x) { 
		//mieszanie podwojne
		int temp = 1;
		int warPoHash = hash(x);
			if (tab[warPoHash].klucz == x) {
				return warPoHash;
			}
			else if (rodzajHashowania == 0) {
				int temp2 = hash2(x);
				warPoHash + temp2;
				while (temp < 997) {
						if (tab[warPoHash].klucz == x) {
							return warPoHash;
						}
					warPoHash + temp2;
					temp++;
					warPoHash = warPoHash % 997;
					
				}
			}
			else {
				//adresowanie liniowe
				warPoHash++;
				
				while (temp < 997) {
					warPoHash %= 997;
					if (tab[warPoHash].klucz == x) {
						return warPoHash;
					}
					warPoHash++;
					temp++;
					
				}
			}
			std::cout << "Brak wartoœci\n";
			return -1;
			
	}

	void usun(int x) {
		int a = find(x);
		if (a == -1) {
			std::cout << "Nie znaleziono\n";
		}
		else {
			tab[a] = -1;
			std::cout << "Obiek usuniêty\n";
		}

	}

	static int hash(Element a) {
		int temp = ((a.klucz % 1000) + (int)pow(2,(a.klucz % 10)) + 1)%997;
		return temp;
	}

	static int hash2(Element a) {
		return ((3*a.klucz)%19)+1;
	}

	Hashing() {
		for (int i = 0; i < 997; i++) {
			tab[i] = 0;
		}
	}

};


int main() {

	double time1, time2;

	int k1, k2, k3, k4, X;
	std::ifstream odczyt("inlab07.txt");

	if (odczyt.is_open())
	{
		odczyt >> X;
		odczyt >> k1;
		odczyt >> k2;
		odczyt >> k3;
		odczyt >> k4;
		odczyt.close();
	}

	clock_t t1 = clock();
	Hashing* k = new Hashing();
	k->rodzajHashowania = 1;
	k->usun(k1);
	k->insert(k1);
	k->wyswietl(0, 100);
	k->insert_x(X);
	k->wyswietl(0, 100);
	k->insert(k2);
	k->insert(k3);
	k->insert(k4);
	k->wyswietl(0, 100);
	k->wyswietl(500, 600);
	clock_t t2 = clock();
	time1 = (double)(t2 - t1) / CLOCKS_PER_SEC;
	std::cout << "Czas przy adresowaniu linowym: " << time1;


	clock_t t3 = clock();
	Hashing* d = new Hashing();
	d->rodzajHashowania = 0;
	d->usun(k1);
	d->insert(k1);
	d->wyswietl(0, 100);
	d->insert_x(X);
	d->wyswietl(0, 100);
	d->insert(k2);
	d->insert(k3);
	d->insert(k4);
	d->wyswietl(0, 100);
	d->wyswietl(500, 600);
	clock_t t4 = clock();
	time2 = (double)(t4 - t3) / CLOCKS_PER_SEC;
	std::cout << "Czas przy mieszaniu podwójnym: " << time2;

	system("pause");
}