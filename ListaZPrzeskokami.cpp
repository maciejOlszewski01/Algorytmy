/* ALGO2 IS1 212B LAB04
Maciej Olszewski
om49360@zut.edu.pl */


#include <iostream>
#include <time.h>
#include <fstream>





class Lista
{
public:
	int klucz;
	double zmienna;
	char znak;
	int wysokosc = 0;
	Lista* adres[10];


	void randomWysokosc(int LMAX);
	Lista(int a);
	Lista();
	~Lista();
};


class Lista_Zbiornik
{
public:
	Lista* poczatek;
	int liczbaWezlow = 0;
	Lista* tail;
	int LMAX;

	void poziomy();
	void add(Lista* a);
	void add_x(int x);
	void add(int x);
	void find(int x);
	Lista* find_adres(int x);
	Lista* find_poprzednik(Lista* a);
	void wyswietl(int y);
	void wyswietl_poziom(int y, int p);
	void wyswietl_ilosc();
	void usun(int x);
	void usun_liste();
	void swap(Lista* a);
	void sort();
	void kalibracja();

	Lista_Zbiornik(int LMAX);
	Lista_Zbiornik();
	~Lista_Zbiornik();
};

int main() {
	int X, k1, k2, k3, k4, k5, LMAX;

	std::ifstream odczyt("inlab03.txt");

	if (odczyt.is_open())
	{

		odczyt >> X;
		odczyt >> LMAX;
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


	Lista_Zbiornik* k = new Lista_Zbiornik(LMAX);
	k->find(k1);
	k->add_x(X);
	k->poziomy();
	k->wyswietl(20);
	for (int i = 0; i < LMAX; i++) {
		k->wyswietl_poziom(20, i);
	}
	k->add(k2);
	k->wyswietl_poziom(20, 0);
	k->add(k3);
	k->wyswietl_poziom(20, 0);
	k->add(k4);
	k->wyswietl_poziom(20, 0);
	k->add(k5);
	k->poziomy();
	for (int i = 0; i < LMAX; i++) {
		k->wyswietl_poziom(20, i);
	}
	k->usun(k3);
	k->usun(k2);
	k->usun(k5);
	k->poziomy();
	for (int i = 0; i < LMAX; i++) {
		k->wyswietl_poziom(20, i);
	}


	koniec = clock();
	time_spend = (double)(koniec - start) / CLOCKS_PER_SEC;

	std::cout << "Czas wykonania: " << time_spend << "\n";

	system("pause");
}


Lista::Lista()
{

	klucz = ((std::rand()) % 99900) + 99;
	for (int i = 0; i < 10; i++) {
		adres[i] = 0;
	}

}

void Lista::randomWysokosc(int LMAX)
{
	while ((rand() % 100 < 0.5 * 100)&(wysokosc < LMAX)) {
		wysokosc++;
	}

}

Lista::Lista(int a)
{

	klucz = a;
	for (int i = 0; i < 10; i++) {
		adres[i] = 0;
	}

}

Lista::~Lista()
{
}



void Lista_Zbiornik::poziomy()
{
	int* tab = new int[LMAX - 1];
	for (int i = 0; i < LMAX; i++) {
		tab[i] = 0;
	}

	Lista* temp = poczatek->adres[0];
	//petla dla kazdego elementu
	for (int i = 1; i <= liczbaWezlow; i++) {
		for (int j = temp->wysokosc; j >= 0; j--) {
			tab[j] += 1;
		}
		temp = temp->adres[0];
	}


	for (int i = 0; i < LMAX; i++) {
		std::cout << "Poziom " << i << " Liczba elementow: " << tab[i] << "\n";
	}

}

void Lista_Zbiornik::add(Lista* a)
{
	a->znak = 'T';
	a->zmienna = std::rand();



	int w = 1;
	if (poczatek->adres[0] == tail) {
		poczatek->adres[0] = a;
		poczatek->adres[0]->adres[0] = tail;
		liczbaWezlow++;
		a->randomWysokosc(LMAX);
	}
	else {
		Lista* temp = poczatek->adres[0];
		while (!(temp->adres[0] == tail)) {
			temp = temp->adres[0];
			if (temp->klucz == a->klucz) {
				std::cout << "BLAD POWTORZONY KLUCZ" << "\n";
				w--;
				temp->znak = 'D';
				break;
			}
		}
		if (w) {
			temp->adres[0] = a;
			a->adres[0] = tail;
			liczbaWezlow++;
			a->randomWysokosc(LMAX);
		}
	}
	sort();
	kalibracja();
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
	if (poczatek->adres[0] == tail) {
		poczatek->adres[0] = a;
		poczatek->adres[0]->adres[0] = tail;
		liczbaWezlow++;
		a->randomWysokosc(LMAX);
	}
	Lista* temp = poczatek->adres[0];
	while (!(temp->adres[0] == tail)) {
		temp = temp->adres[0];
		if (temp->klucz == a->klucz) {
			std::cout << "BLAD POWTORZONY KLUCZ" << "\n";
			w--;
			temp->znak = 'D';
			break;
		}
	}
	if (w) {
		temp->adres[0] = a;
		a->adres[0] = tail;
		liczbaWezlow++;
		a->randomWysokosc(LMAX);
	}

	sort();
	kalibracja();
}

void Lista_Zbiornik::find(int x)
{
	int w = 1;
	Lista* temp = poczatek->adres[0];
	if (!(temp->adres[0] == nullptr)) {
		while (temp->adres[0]) {
			if (temp->klucz == x) {
				std::cout << "ZNALEZIONO \n" << temp->klucz << " " << temp->znak << " " << temp->zmienna << "\n";
				w--;
			}
			temp = temp->adres[0];
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

	Lista* temp = poczatek->adres[0];
	while (temp->adres[0]) {
		if (temp->klucz == x) {
			return temp;
		}
		temp = temp->adres[0];
		if (temp->adres[0] == 0) {
			if (temp->klucz == x) {
				return temp;
			}
		}
	}
	return nullptr;

}

Lista * Lista_Zbiornik::find_poprzednik(Lista * a)
{
	Lista* temp = poczatek->adres[0];
	while (temp->adres[0]) {
		if (temp->adres[0] == a) {
			return temp;
		}
		temp = temp->adres[0];
	}
}

void Lista_Zbiornik::wyswietl(int y)
{
	Lista* temp = poczatek->adres[0];



	std::cout << 0 << ". " << temp->klucz << " " << temp->wysokosc << "\n";

	for (int i = 1; i < y; i++) {
		if (temp->adres[0]->adres[0] == 0) {
			std::cout << "Brak kolejnego elementu" << "\n";
			break;
		}
		temp = temp->adres[0];
		std::cout << i << ". " << temp->klucz << " " << temp->wysokosc << "\n";


	}


}

void Lista_Zbiornik::wyswietl_poziom(int y, int p)
{
	std::cout << "\n" << "POZIOM " << p << "\n";

	Lista* temp = poczatek->adres[p];
	if (temp == tail) {
		std::cout << "Brak kolejnego elementu" << "\n";
	}
	else {

		for (int i = 0; (i < y); i++) {
			if ((temp == tail)) {
				std::cout << "Brak kolejnego elementu" << "\n";
				break;
			}
			std::cout << i << ". " << temp->klucz << " " << temp->wysokosc << "\n";


			temp = temp->adres[p];
			if ((temp == nullptr)) {
				std::cout << "Brak kolejnego elementu" << "\n";
				break;
			}

		}

	}

}

void Lista_Zbiornik::wyswietl_ilosc()
{
	std::cout << "Ilosc elementow" << liczbaWezlow << "\n";
}


//Tutaj bedzie kombinowanie
void Lista_Zbiornik::usun(int x)
{

	Lista* temp = find_adres(x);
	if (temp == nullptr) {
		std::cout << "Nie znaleziono elementu" << "\n";
	}
	else if (temp == poczatek->adres[0]) {
		Lista* temp2 = poczatek->adres[0];
		while (temp->wysokosc) {
			temp2->adres[temp->wysokosc] = temp->adres[temp->wysokosc];
			temp->wysokosc--;
		}
		poczatek->adres[0] = temp2->adres[0];
		delete temp2;
		liczbaWezlow--;
		kalibracja();
	}
	else if (!(temp->adres[0] == 0)) {
		Lista* temp2 = find_poprzednik(temp);
		while (temp->wysokosc) {
			temp2->adres[temp->wysokosc] = temp->adres[temp->wysokosc];
			temp->wysokosc--;
		}
		temp2->adres[0] = temp->adres[0];
		delete temp;
		liczbaWezlow--;
		kalibracja();
	}
	else {
		Lista* temp2 = find_poprzednik(temp);
		delete temp2->adres[0];
		while (temp->wysokosc) {
			temp2->adres[temp->wysokosc] = tail;
			temp->wysokosc--;
		}
		temp2->adres[0] = tail;
		liczbaWezlow--;
		kalibracja();
	}
}

void Lista_Zbiornik::usun_liste()
{
	Lista* temp = 0;
	int i = 0;
	while (i <= liczbaWezlow) {
		Lista* temp2 = poczatek;
		while (!(temp2->adres[0] == 0)) {
			if (temp2->adres[0] == temp) {

				delete temp2->adres[0];
				i++;
			}
			temp2 = temp2->adres[0];
			if (temp2->adres[0] == temp) {
				delete temp2->adres[0];
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
	if (a == poczatek->adres[0]) {

		temp = a;
		poczatek->adres[0] = a->adres[0];
		a->adres[0] = a->adres[0]->adres[0];
		poczatek->adres[0]->adres[0] = a;
	}
	else {
		temp = find_poprzednik(a);
		temp->adres[0] = a->adres[0];
		a->adres[0] = a->adres[0]->adres[0];
		temp->adres[0]->adres[0] = a;

	}



}

void Lista_Zbiornik::sort()
{
	Lista* temp7 = poczatek;
	if (liczbaWezlow > 1) {
		for (int i = 0; i < liczbaWezlow; i++) {
			temp7 = poczatek->adres[0];
			do {
				if (temp7->adres[0]->adres[0] == 0) {
					break;
				}
				if (temp7->klucz > temp7->adres[0]->klucz) {
					swap(temp7);

				}
				else {
					temp7 = temp7->adres[0];
				}
			} while (temp7->adres[0]->adres[0]);
		}
	}
}

void Lista_Zbiornik::kalibracja()
{
	Lista* temp = poczatek;
	Lista* temp2 = poczatek;
	//petla dla kazdego elementu
	for (int i = 1; i < liczbaWezlow; i++) {
		//pentla dla kazdego poziomu
		for (int j = 1; j <= temp->wysokosc; j++) {
			temp2 = temp->adres[0];
			while ((temp2->wysokosc < j)) {

				temp2 = temp2->adres[0];


			}
			temp->adres[j] = temp2;
		}

		temp = temp->adres[0];
	}
}

Lista_Zbiornik::Lista_Zbiornik(int TLMAX)
{
	LMAX = TLMAX;
	poczatek = new Lista();
	poczatek->wysokosc = TLMAX;
	tail = new Lista();
	tail->wysokosc = TLMAX;
	for (int i = 0; i < TLMAX; i++) {
		poczatek->adres[i] = tail;
	}
}

Lista_Zbiornik::Lista_Zbiornik()
{
	LMAX = 9;
	poczatek = new Lista();
	poczatek->wysokosc = 9;
	tail = new Lista();
	tail->wysokosc = 9;
	for (int i = 0; i < 9; i++) {
		poczatek->adres[i] = tail;
	}
}


Lista_Zbiornik::~Lista_Zbiornik()
{
}