//ALGO2 IS1 212B LAB08
//Maciej Olszewski
//om49360@zut.edu.pl

#include <iostream>
#include<time.h>
#include <cstdlib>



template <typename t> class  Wezel
{
public:
	int klucz;
	t dane;


	bool operator >(const Wezel<t>& a) {
		if (klucz > a.klucz) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator <(const Wezel<t>& a) {
		if (klucz < a.klucz) {
			return true;
		}
		else {
			return false;
		}
	}


	Wezel() {
		klucz = std::rand();
	}
	~Wezel() {}
};

template <typename T>
class dynamic_array
{
public:

	int size = 2;
	Wezel<T>* start = new Wezel<T>[2];
	int real_size = 0;



	static const int rozszerzenie = 2;

	void size_up()
	{
		size = size * rozszerzenie;

		Wezel<T>* tab = new Wezel<T>[size];
		for (int i = 0; i < real_size; i++) {
			tab[i] = start[i];
		}
		delete[] start;
		start = tab;
	}

	void add(Wezel<T> a)
	{
		if (real_size + 1 == size) {
			size_up();
		}
		start[real_size + 1] = a;
		przekopcowanie_w_gore(real_size + 1);
		real_size++;

	}



	void clear()
	{
		delete[] start;
		size = 2;
		start = new Wezel<T>[2];
		real_size = 0;
	}

	void to_string()
	{
		for (int i = 0; i < real_size; i++) {
			std::cout << i + 1 << ". ";


			std::cout << start[i + 1].klucz << "\n";
		}
	}


	Wezel<T> usun_korzen() {
		if (real_size == 0) {
			std::cout << "Kopiec pusty zwrócono œmieciow¹ wartoœæ";
			return start[0];
		}
		Wezel<T> temp = start[1];
		start[1] = start[real_size];

		przekopcowanie_w_dol(1);
		real_size--;
		return temp;
	}


	void przekopcowanie_w_dol(int a) {
		Wezel< T> temp;
		if (a * 2 + 1 <= real_size) {
			if ((start[a * 2] > start[a * 2 + 1])) {
				if (start[a * 2] > start[a]) {
					temp = start[a * 2];
					start[a * 2] = start[a];
					start[a] = temp;
					przekopcowanie_w_dol(a * 2);
				}
			}
			else
				if (start[a * 2] < start[a * 2 + 1]) {
					if (start[a * 2 + 1] > start[a]) {
						temp = start[a * 2 + 1];
						start[a * 2 + 1] = start[a];
						start[a] = temp;
						przekopcowanie_w_dol(a * 2 + 1);
					}
				}
		}
		else if (a * 2 <= real_size)
		{
			if (start[a * 2] > start[a]) {
				temp = start[a * 2];
				start[a * 2] = start[a];
				start[a] = temp;
			}
		}
		else {

		}
	}

	void przekopcowanie_w_gore(int a) {
		if ((start[a] > start[a / 2]) && (a / 2 != 0)) {
			Wezel<T> temp = start[a / 2];
			start[a / 2] = start[a];
			start[a] = temp;
			przekopcowanie_w_gore(a / 2);
		}
	}




	dynamic_array()
	{
	}

	~dynamic_array()
	{
		delete[] start;
	}


};




int main() {

	dynamic_array<char>* a = new dynamic_array<char>();
	int n = 10;
	for (int i = 1; i <= 7; i++) {
		
			
		
		
		double pomiar;
		clock_t t1 = clock();
		for (int j = 0; j < n; j++) {
			Wezel<char> c;
			a->add(c);
		}
		clock_t t2 = clock();
		for (int k = 0; k < 5; k++) {
			std::cout << k + 1 << " " << a->start[k + 1].klucz << "\n";
		}
		std::cout << "Ilosc elementow: " << a->real_size << "\n";
		pomiar = (double)(t2 - t1) / CLOCKS_PER_SEC;
		std::cout << "Czas dodawania przy n: " << n << " Wynosi: " << pomiar << "\n";




		t1 = clock();
		for (int k = 0; k < n; k++) {
			Wezel<char> polled = a->usun_korzen();
		}
		t2 = clock();

		std::cout << "Ilosc elementow: " << a->real_size << "\n";
		pomiar = (double)(t2 - t1) / CLOCKS_PER_SEC;
		std::cout << "Czas usuwania przy n: " << n << " Wynosi: " << pomiar << "\n";

		
		a->clear();
		n = n * 10;


	}
	delete a;

	system("pause");
}