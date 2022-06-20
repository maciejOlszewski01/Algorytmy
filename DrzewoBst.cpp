/*ALGO2 IS1 212B LAB05
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


	Wezel(t a) {
		dane = a;
		klucz = rand();
	}


	Wezel() {
		klucz = rand();

	};

	~Wezel() {

	};
};


template<typename t>
class Tree
{
public:
	int rozmiar = 0;
	int ilosc_elementow = 0;
	Wezel<t>* root = 0;




	void insert(Wezel<t>* a)
	{

		if (root == 0) {
			root = a;
			rozmiar = 1;
			ilosc_elementow++;
		}
		else {
			int temp2 = 1;
			bool wlozony = false;
			Wezel<t>* temp = root;
			while (!wlozony) {
				temp2++;
				if (temp == NULL) {
					std::cout << "POWTÓRZENIE KLUCZA";
					break;
				}
				if (temp->klucz > a->klucz) {
					if (temp->lPotomek != 0) {
						temp = temp->lPotomek;
						continue;
					}
					else {
						temp->lPotomek = a;
						temp->lPotomek->rodzic = temp;
						wlozony = true;
						ilosc_elementow++;
					}
				}

				if (temp->klucz < a->klucz) {
					if (temp->pPotomek != 0) {
						temp = temp->pPotomek;
						continue;
					}
					else {
						temp->pPotomek = a;
						temp->pPotomek->rodzic = temp;
						wlozony = true;
						ilosc_elementow++;
					}

				}

			}
			if (temp2 > rozmiar) {
				rozmiar = temp2;
			}



		}
	}
	;

	Wezel<t>* find(int a) {
		Wezel<t> * temp = root;
		if (a == root->klucz) {
			return root;
		}
		else {
			while (!(temp == NULL)) {

				if (a < temp->klucz) {
					temp = temp->lPotomek;
				}
				else if (a > temp->klucz) {
					temp = temp->pPotomek;
				}
				else {
					break;
				}




			}
		}
		return temp;
	}
	static void przejsciePreOrder(Wezel<t> *a) {
		if (a != NULL) {
			std::cout << "Wartosc klucza " << a->klucz << " Dane: " << a->dane << " \n";
			przejsciePreOrder(a->lPotomek);
			przejsciePreOrder(a->pPotomek);

		}
	}

	static void przejsciePreOrder(Wezel<t> *a, int c) {

		int temp = c;
		if (a != NULL) {
			std::cout << temp << " Poziom " << "Wartosc klucza " << a->klucz << " Dane: " << a->dane << " \n";
			temp++;
			przejsciePreOrder(a->lPotomek, temp);
			przejsciePreOrder(a->pPotomek, temp);
			temp--;
		}
	}

	static void przejscieInOrder(Wezel<t> *a) {
		if (a != NULL) {
			przejscieInOrder(a->lPotomek);
			std::cout << "Wartosc klucza " << a->klucz << " Dane: " << a->dane << " \n";
			przejscieInOrder(a->pPotomek);

		}
	}

	void to_string() {
		std::cout << rozmiar << " Wysokosc" << "\n" << ilosc_elementow << " ilosc elementow" << "\n";
		przejsciePreOrder(root, 1);

	}
	int getWysokosc() {
		return rozmiar;
	}

	void usun(int a) {
		Wezel<t>* temp = find(a);
		if (temp == NULL) {
			std::cout << "BRAK TAKIEGO ELEMENTU";
		}
		else if ((temp->lPotomek == NULL) & (temp->pPotomek == NULL)) {
			Wezel<t>* temp2 = temp->rodzic;
			if (temp2->klucz > temp->klucz) {

				temp2->lPotomek = NULL;
			}
			else {

				temp2->pPotomek = NULL;
			}
			ilosc_elementow--;
		}
		else if ((!(temp->lPotomek == NULL)) & (!(temp->pPotomek == NULL))) {
			Wezel<t>* temp2 = findNastepnik(temp->pPotomek);
			if (temp->pPotomek != NULL) {
				usun(temp2->klucz);
				temp->rodzic->pPotomek = temp2;
				temp2->pPotomek = temp->pPotomek;
				temp2->lPotomek = temp->lPotomek;
				temp2->rodzic = temp->rodzic;

				temp = temp2;

			}
			else {
				temp2->pPotomek = temp->pPotomek;
				temp2->lPotomek = temp->lPotomek;
				temp2->rodzic = temp->rodzic;
				temp = temp2;
			}
		}
		else if ((!(temp->lPotomek == NULL)) | (!(temp->pPotomek == NULL))) {
			Wezel<t>* temp2 = temp->rodzic;
			Wezel<t>* temp3;
			if (temp2->klucz > temp->klucz) {
				if (temp->lPotomek == NULL) {
					temp3 = temp->pPotomek;
				}
				else {
					temp3 = temp->lPotomek;
				}
				temp2->lPotomek = temp3;

			}
			else {
				if (temp->lPotomek == NULL) {
					temp3 = temp->pPotomek;
				}
				else {
					temp3 = temp->lPotomek;
				}
				temp2->pPotomek = temp3;

			}
			ilosc_elementow--;




		}


	}
	static Wezel<t> * findNastepnik(Wezel<t>* a) {
		Wezel<t>* temp = a;
		while (temp->lPotomek != NULL) {
			temp = temp->lPotomek;
		}
		return temp;
	}

	static Wezel<t> * findPoprzednik(Wezel<t>* a) {
		Wezel<t>* temp = a;
		while (temp->pPotomek != NULL) {
			temp = temp->pPotomek;
		}
		return temp;
	}

	Tree() {
	};
	~Tree() {
	};
};




int main() {
	Wezel<int>* a = new Wezel<int>(2137);
	Tree<int>* drzewo = new Tree<int>();
	double t_max_f = 0;
	double t_max_a = 0;

	int N = 10 * 10 * 10 * 10 * 10 * 10 * 10;
	for (int i = 0; i < N; i++) {
		clock_t t1 = clock();
		drzewo->insert(a);
		a = new Wezel<int>(i);
		clock_t t2 = clock();
		if ((double)(t2 - t1) > t_max_a) {
			t_max_a = (double)(t2 - t1) / CLOCKS_PER_SEC;
		}

	}
	for (int i = 0; i < N; i++) {
		clock_t t1 = clock();
		drzewo->find(rand());
		a = new Wezel<int>(i);
		clock_t t2 = clock();
		if ((double)(t2 - t1) > t_max_f) {
			t_max_f = (double)(t2 - t1) / CLOCKS_PER_SEC;
		}

	}

	std::cout << t_max_f << "\n" << t_max_a << "\n";

	//metoda to string przedstawia i rozmiar(wysokoœæ) i iloœæ elementów mo¿na ³atwo odczytaæ stosunek
	drzewo->to_string();





	system("pause");

}