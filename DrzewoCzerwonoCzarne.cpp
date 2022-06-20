/*ALGO2 IS1 212B LAB06
Maciej Olszewski
om49360@zut.edu.pl
*/

#include <iostream>
#include <time.h>

template<typename t> class Wezel
{
public:
	Wezel<t>* lPotomek = NULL;
	Wezel<t>* pPotomek = NULL;
	Wezel<t>* rodzic = NULL;
	t dane;
	int klucz;
	// 0 = czarny 1 = czerwony;
	bool kolor;

	Wezel(t a) {
		dane = a;
		klucz = 10 * (rand() + rand() + rand() +rand() + rand() + rand())+ 10 * (rand() + rand() + rand()) +  10*(rand() + rand() + rand())+(rand() + rand() + rand())/2+ (rand() + rand() + rand()) / 2;
		kolor = 1;
	}


	Wezel() {
		klucz = 10 * (rand() + rand() + rand() + rand() + rand() + rand())+ 10 * (rand() + rand() + rand())+ 10 * (rand() + rand() + rand()) + (rand() + rand() + rand()) / 2 + (rand() + rand() + rand()) / 2;
		kolor = 1;
	};

	~Wezel() {

	};
};


template<typename t>
class Tree
{
public:

	int ilosc_elementow = 0;
	Wezel<t>* root = 0;
	Wezel<t> nic;



	void insert(Wezel<t>* a)
	{

		if (root == 0) {
			root = a;
			
			ilosc_elementow++;
			a->lPotomek = &nic;
			a->pPotomek = &nic;
			a->rodzic = &nic;
		}
		else {
			
			bool wlozony = false;
			Wezel<t>* temp = root;
			while (!wlozony) {
				
				
				if (temp->klucz > a->klucz) {
					if (temp->lPotomek != nic.lPotomek) {
						temp = temp->lPotomek;
						continue;
					}
					else {
						temp->lPotomek = a;
						temp->lPotomek->rodzic = temp;
						wlozony = true;
						
					}
				}

				if (temp->klucz < a->klucz) {
					if (temp->pPotomek != nic.lPotomek) {
						temp = temp->pPotomek;
						continue;
					}
					else {
						temp->pPotomek = a;
						temp->pPotomek->rodzic = temp;
						wlozony = true;
					
					}



				}
				if (temp->klucz == a->klucz) {
					std::cout << "\nPowtórzenie klucza\n";
					break;
				}

			}
			if (wlozony) {
				a->lPotomek = &nic;
				a->pPotomek = &nic;
				ilosc_elementow++;
				
				przywroc_wlasciwosci(a);
			}
		}
		root->kolor = 0;
	}
	void przywroc_wlasciwosci(Wezel<t>* a) {
		while (a->rodzic->kolor == 1) {
			//lewa 1
			if (a->rodzic->klucz < a->rodzic->rodzic->klucz) {
				if (a->rodzic->rodzic->pPotomek->kolor == 1) {
					a->rodzic->rodzic->pPotomek->kolor = 0;
					a->rodzic->rodzic->kolor = 1;
					a->rodzic->kolor = 0;
					//ta linia
					a = a->rodzic->rodzic;
					continue;
				}
				if (a->klucz > a->rodzic->klucz) {
					//zobzacz jak vez taj lini
					a = a->rodzic;
					obrot_w_lewo(a);
				}

				a->rodzic->kolor = 0;
				a->rodzic->rodzic->kolor = 1;
				obrot_w_prawo(a->rodzic->rodzic);
				break;

			}
			//prawa
			else {
				if (a->rodzic->rodzic->lPotomek->kolor == 1) {
					a->rodzic->rodzic->lPotomek->kolor = 0;
					a->rodzic->rodzic->kolor = 1;
					a->rodzic->kolor = 0;
					//ta linia
					a = a->rodzic->rodzic;
					continue;
				}
				if (a->klucz < a->rodzic->klucz) {
					//zobzacz jak vez taj lini
					a = a->rodzic;
					obrot_w_prawo(a);
				}

				a->rodzic->kolor = 0;
				a->rodzic->rodzic->kolor = 1;
				obrot_w_lewo(a->rodzic->rodzic);
				break;
			}
		}
	}

	Wezel<t>* find(int a) {
		Wezel<t>* temp = root;
		if (a == root->klucz) {
			return root;
		}
		else {
			while (!(temp == nic.lPotomek)) {

				if (a < temp->klucz) {
					temp = temp->lPotomek;
				}
				else if (a > temp->klucz) {
					temp = temp->pPotomek;
				}
				else  {
					break;
				}
			}
		}
		if (temp == &nic) {
			std::cout << "\nNie znaleziono\n";
			return NULL;
		}
		std::cout << "\nZnaleziono";
		return temp;
	}

	static void przejsciePreOrder(Wezel<t>* a, int c, Wezel<t> d) {

		int temp = c;
		if (a != d.lPotomek) {
			std::cout << temp << " Poziom " << "Wartosc klucza " << a->klucz << " Dane: " << a->dane;
			if (a->kolor == 1) {
				std::cout << " Kolor: Czerwony\n";
			}
			else {
				std::cout << " Kolor: Czarny\n";
			}
			temp++;
			przejsciePreOrder(a->lPotomek, temp, d);
			przejsciePreOrder(a->pPotomek, temp, d);
			temp--;
		}
	}

	static void przejscieInOrder(Wezel<t>* a) {
		if (a != a->rodzic) {
			przejscieInOrder(a->lPotomek);
			std::cout << "Wartosc klucza " << a->klucz << " Dane: " << a->dane;
			if (a->kolor == 1) {
				std::cout << " Kolor: Czerwony\n";
			}
			else {
				std::cout << " Kolor: Czarny\n";
			}
			przejscieInOrder(a->pPotomek);

		}
	}

	void to_string() {
		std::cout << getWysokosc() << " Wysokosc" << "\n" << ilosc_elementow << " ilosc elementow" << "\n";
		przejsciePreOrder(root, 1, nic);

	}
	int getWysokosc() {
		Wezel<t>* temp = root;
		//  Zaczynam od jeden bo petla while nie z³apie leafa ostatniego
		int wysokosc = 1;
		while (temp != temp->rodzic) {
			if (temp->kolor == 0) {
				wysokosc++;
			}
			temp = temp->lPotomek;
		}
		return wysokosc;
	}

	void obrot_w_lewo(Wezel<t>* a) {
		if (a->pPotomek != &nic) {
			Wezel<t>* temp2 = a->pPotomek;
			Wezel<t>* temp = a->rodzic;
			temp2->rodzic = temp;

			
			a->pPotomek = temp2->lPotomek;
			if (temp2->lPotomek != &nic) {
				temp2->lPotomek->rodzic = a;
			}

			temp2->lPotomek = a;
			
			a->rodzic = temp2;
			
			if (temp->lPotomek == a) {
				temp->lPotomek = temp2;
			}
			else if(temp->pPotomek == a) {
				temp->pPotomek = temp2;
			}
			else {
				root = temp2;
			}
		}

	}

	void obrot_w_prawo(Wezel<t>* a) {
		if (a->lPotomek != &nic) {
			Wezel<t>* temp2 = a->lPotomek;
			Wezel<t>* temp = a->rodzic;
			temp2->rodzic = temp;


			a->lPotomek = temp2->pPotomek;
			if (temp2->pPotomek != &nic) {
				
				temp2->pPotomek->rodzic = a;
			}

			temp2->pPotomek = a;

			a->rodzic = temp2;

			if (temp->lPotomek == a) {
				temp->lPotomek = temp2;
			}
			else if (temp->pPotomek == a) {
				temp->pPotomek = temp2;
			}
			else {
				root = temp2;
			}
		}

	}
	static void czysc(Wezel<t>* a) {
		if (a != a->rodzic) {
			czysc(a->pPotomek);
			czysc(a->lPotomek);
			delete a;
		}
	}

	
	static Wezel<t>* findNastepnik(Wezel<t>* a) {
		Wezel<t>* temp = a->pPotomek;
		while (temp->lPotomek != &nic) {
			temp = temp->lPotomek;
		}
		return temp;
	}

	static Wezel<t>* findPoprzednik(Wezel<t>* a) {
		Wezel<t>* temp = a->lPotomek;
		while (temp->pPotomek != &nic) {
			temp = temp->pPotomek;
		}
		return temp;
	}

	Tree() {
		nic.lPotomek = &nic;
		nic.pPotomek = &nic;
		nic.rodzic = &nic;
		nic.kolor = 0;

	};
	~Tree() {
	};
};




int main() {
	Wezel<int>* a = new Wezel<int>(2137);
	Tree<int>* drzewo = new Tree<int>();
	double t_max_f = 0;
	double t_max_a = 0;
	double t_max_fs = 0;
	double t_max_as = 0;
	double t_max_fc = 0;
	double t_max_ac = 0;
	
	int traf;
	int N = 10;

	//zmienic na mniejsze j po mniejsza potege
	for (int j = 1; j < 7; j++) {
		traf = 0;
		clock_t t3 = clock();
		for (int i = 0; i < N; i++) {
			a = new Wezel<int>(i);
			clock_t t1 = clock();
			drzewo->insert(a);
			std::cout << "\ndodano element\n" << i;

			
			clock_t t2 = clock();
			
			if ((double)(t2 - t1) > t_max_a) {
				t_max_a = (double)(t2 - t1) / CLOCKS_PER_SEC;
			}
			
		}
		clock_t t4 = clock();
		t_max_ac = (double)(t4 - t3) / CLOCKS_PER_SEC;
		clock_t t5 = clock();
		for (int i = 0; i < N; i++) {
			clock_t t1 = clock();
			a = drzewo->find(10 * (rand() + rand() + rand() + rand() + rand() + rand()) + 10 * (rand() + rand() + rand()) + 10 * (rand() + rand() + rand()) + (rand() + rand() + rand()) / 2 + (rand() + rand() + rand()) / 2);
			clock_t t2 = clock();
			if (a != NULL) {
				traf++;
			}
			if ((double)(t2 - t1) > t_max_f) {
				t_max_f = (double)(t2 - t1) / CLOCKS_PER_SEC;
			}

		}

		clock_t t6 = clock();
		t_max_fc = (double)(t6 - t5) / CLOCKS_PER_SEC;
		
		t_max_fs = t_max_fc/N;
		t_max_as = t_max_ac / N;
		std::cout <<"\n" << t_max_f << " -> Maksymalny czas wyszukiwania.\n" << t_max_a << " -> Maksymalny czas dodawania\n";
		std::cout << "\n" << t_max_fs << " -> Œredni czas wyszukiwania.\n" << t_max_as << " -> Œredni czas dodawania\n";
		std::cout << "\n" << t_max_fc << " -> Ca³kowity czas wyszukiwania.\n" << t_max_ac << " -> ca³kowity czas dodawania\n" << " Wysokosc: " << drzewo->getWysokosc() << "\n" << "Znaleziono: " << traf;
		N = N *10;
	}
	//metoda to string przedstawia i rozmiar(wysokoœæ) i iloœæ elementów mo¿na ³atwo odczytaæ stosunek
	
	
	//drzewo->to_string();
	

	Tree<int>::czysc(drzewo->root);
	system("pause");

}