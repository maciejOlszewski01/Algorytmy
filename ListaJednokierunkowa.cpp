/* ALGO2 IS1 212B LAB03
Maciej Olszewski
om49360@zut.edu.pl */



#include <iostream>
#include <fstream>
#include <time.h>
#pragma warning(disable : 4996)


class Lista
{
public:
	int klucz;
	double zmienna;
	char znak;
	Lista* adres;



	Lista(int a);
	Lista();
	~Lista();
};


class Lista_Zbiornik
{
public:
	Lista* poczatek = 0;
	int liczbaWezlow = 0;


	void add(Lista* a);
	void add_x(int x);
	void add(int x);
	void find(int x);
	Lista* find_adres(int x);
	Lista* find_poprzednik(Lista* a);
	void wyswietl(int y);
	void wyswietl_ilosc();
	void wywietl_od_konca(int z);
	void usun(int x);
	void usun_liste();
	void swap(Lista* a);
	void sort();

	Lista_Zbiornik();
	~Lista_Zbiornik();
};



int main() {
	int X, k1, k2, k3, k4, k5;

	std::ifstream odczyt("inlab02.txt");

	if (odczyt.is_open())
	{

		odczyt >> X;
		odczyt >> k1;
		odczyt >> k2;
		odczyt >> k3;
		odczyt >> k4;
		odczyt >> k5;

		odczyt.close();
	}

	clock_t start, koniec;
	double time_spend;
	start = clock();




	Lista_Zbiornik* k = new Lista_Zbiornik();
	k->find(k1);
	k->add_x(X);
	k->wyswietl_ilosc();
	k->wyswietl(20);
	k->add(k2);
	k->wyswietl(20);
	k->add(k3);
	k->wyswietl(20);
	k->add(k4);
	k->wyswietl(20);
	k->add(k5);
	k->usun(k3);
	k->wyswietl(20);
	k->usun(k2);
	k->wyswietl(20);
	k->usun(k5);
	k->wyswietl_ilosc();
	k->find(k5);
	k->wywietl_od_konca(11);
	k->wyswietl_ilosc();
	k->usun_liste();




	koniec = clock();
	time_spend = (double)(koniec - start) / CLOCKS_PER_SEC;

	std::cout << "Czas wykonania: " << time_spend << "\n";

	system("pause");
}


Lista::Lista()
{
	klucz = ((std::rand()) % 99900) + 99;
	adres = 0;

}

Lista::Lista(int a)
{
	klucz = a;
	adres = 0;

}

Lista::~Lista()
{
}

void Lista_Zbiornik::add(Lista* a)
{
	a->znak = 'T';
	a->zmienna = std::rand();



	int w = 1;
	if (poczatek == 0) {
		poczatek = a;
		liczbaWezlow++;
	}
	Lista* temp = poczatek;
	while (temp->adres) {
		temp = temp->adres;
		if (temp->klucz == a->klucz) {
			std::cout << "BLAD POWTORZONY KLUCZ" << "\n";
			w--;
			break;
		}
	}
	if (w) {
		temp->adres = a;
		a->adres = 0;
		liczbaWezlow++;
	}
	sort();

}



void Lista_Zbiornik::add_x(int x)
{
	for (int i = 0; i < x; i++) {
		Lista * temp = new Lista();
		//std::cout << temp->klucz << " ";
		add(temp);

	}
}

void Lista_Zbiornik::add(int x)
{
	Lista* a = new Lista(x);

	a->znak = 'T';
	a->zmienna = std::rand();



	int w = 1;
	if (poczatek == 0) {
		poczatek = a;
		liczbaWezlow++;
	}
	Lista* temp = poczatek;
	while (temp->adres) {
		temp = temp->adres;
		if (temp->klucz == a->klucz) {
			std::cout << "BLAD POWTORZONY KLUCZ" << "\n";
			w--;
			break;
		}
	}
	if (w) {
		temp->adres = a;
		a->adres = 0;
		liczbaWezlow++;
	}

	sort();
}

void Lista_Zbiornik::find(int x)
{
	int w = 1;
	Lista* temp = poczatek;
	if (!(temp == nullptr)) {
		while (temp->adres) {
			if (temp->klucz == x) {
				std::cout << "ZNALEZIONO \n" << temp->zmienna << " " << temp->znak << " " << temp->zmienna << "\n";
				w--;
			}
			temp = temp->adres;
			if (temp->adres == 0) {
				if (temp->klucz == x) {
					std::cout << "ZNALEZIONO \n" << temp->zmienna << " " << temp->znak << " " << temp->zmienna << "\n";
					w--;
				}
			}
		}
		if (w) {
			std::cout << "NIE ZNALEZIONO" << "\n";
		}
	}
	else {
		std::cout << "Tablica pusta" << "\n";
	}
}

Lista * Lista_Zbiornik::find_adres(int x)
{

	Lista* temp = poczatek;
	while (temp->adres) {
		if (temp->klucz == x) {
			return temp;
		}
		temp = temp->adres;
		if (temp->adres == 0) {
			if (temp->klucz == x) {
				return temp;
			}
		}
	}
	return nullptr;

}

Lista * Lista_Zbiornik::find_poprzednik(Lista * a)
{
	Lista* temp = poczatek;
	while (temp->adres) {
		if (temp->adres == a) {
			return temp;
		}
		temp = temp->adres;
	}
}

void Lista_Zbiornik::wyswietl(int y)
{
	Lista* temp = poczatek;



	std::cout << 0 << ". " << temp->klucz << "\n";

	for (int i = 1; i < y; i++) {
		if (temp->adres == 0) {
			std::cout << "Brak kolejnego elementu" << "\n";
			break;
		}
		temp = temp->adres;
		std::cout << i << ". " << temp->klucz << "\n";


	}


}

void Lista_Zbiornik::wyswietl_ilosc()
{
	std::cout << "Ilosc elementow" << liczbaWezlow << "\n";
}

void Lista_Zbiornik::wywietl_od_konca(int z)
{
	Lista* temp = 0;
	int i = 0;
	while (i < z) {
		Lista* temp2 = poczatek;
		while (!(temp2->adres == 0)) {
			if (temp2->adres == temp) {

				std::cout << i << ". " << temp2->klucz << "\n";
				i++;
				temp = temp2;
			}
			temp2 = temp2->adres;
			if (temp2->adres == temp) {

				std::cout << i << ". " << temp2->klucz << "\n";
				i++;
				temp = temp2;
			}
		}
		if (temp == poczatek && i != z) {
			std::cout << "Brak kolejnych elementow" << "\n";
			break;
		}
	}
}

void Lista_Zbiornik::usun(int x)
{

	Lista* temp = find_adres(x);
	if (temp == nullptr) {
		std::cout << "Nie znaleziono elementu" << "\n";
	}
	else if (temp == poczatek) {
		Lista* temp2 = poczatek;
		poczatek = temp2->adres;
		delete temp2;
		liczbaWezlow--;
	}
	else if (!(temp->adres == 0)) {
		Lista* temp2 = find_poprzednik(temp);
		temp2->adres = temp->adres;
		delete temp;
		liczbaWezlow--;
	}
	else {
		Lista* temp2 = find_poprzednik(temp);
		delete temp2->adres;
		temp2->adres = 0;
		liczbaWezlow--;
	}
}

void Lista_Zbiornik::usun_liste()
{
	Lista* temp = 0;
	int i = 0;
	while (i <= liczbaWezlow) {
		Lista* temp2 = poczatek;
		while (!(temp2->adres == 0)) {
			if (temp2->adres == temp) {

				delete temp2->adres;
				i++;
			}
			temp2 = temp2->adres;
			if (temp2->adres == temp) {
				delete temp2->adres;
				i++;
			}
		}
		if (i == liczbaWezlow) {
			std::cout << "Brak kolejnych elementow tablica usunieta";
			break;
		}
	}
	liczbaWezlow = 0;
}

void Lista_Zbiornik::swap(Lista * a)
{

	Lista* temp;
	if (a == poczatek) {

		temp = a;
		poczatek = a->adres;
		a->adres = a->adres->adres;
		poczatek->adres = a;
	}
	else {
		temp = find_poprzednik(a);
		temp->adres = a->adres;
		a->adres = a->adres->adres;
		temp->adres->adres = a;

	}



}

void Lista_Zbiornik::sort()
{
	Lista* temp7 = poczatek;
	if (liczbaWezlow > 1) {
		for (int i = 0; i < liczbaWezlow; i++) {
			temp7 = poczatek;
			do {
				if (temp7->adres == 0) {
					break;
				}
				if (temp7->klucz > temp7->adres->klucz) {
					swap(temp7);

				}
				else {
					temp7 = temp7->adres;
				}
			} while (temp7->adres);
		}
	}
}

Lista_Zbiornik::Lista_Zbiornik()
{
}


Lista_Zbiornik::~Lista_Zbiornik()
{
}


