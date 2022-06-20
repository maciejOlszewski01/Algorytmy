// ALGO2 IS1 212B LAB02
// Maciej Olszewski
// om49360@zut.edu.pl


#include<time.h>
#include<iostream>
#include<cstdlib>

template <typename T>
class dynamic_array
{
public:
	int size = 1;
	T *start = new T[1];
	int real_size = 0;


	//POWIEKSZENIE ROZMIARU
	void size_up();

	//A juz zrobione
	void add(T a);

	//B
	T show_status(int i);
	//C
	void replace(int a, T b);
	//D
	void clear();
	//E
	void to_string();
	//F
	void sort();

	dynamic_array();

	~dynamic_array();
};

int main() {

	const int n = pow(10, 7); 
	int pozycjamax;
	clock_t t1 = clock();
	double max_operation_time;
	dynamic_array<double> K;
	double max_time_per_element = 0;
	for (int i = 0; i < n; i++) {
		clock_t t1_element = clock();
		K.add(rand());
		clock_t t2_element = clock();
		double time_per_element = t2_element - t1_element;
		if (time_per_element > max_time_per_element)
		{
			max_time_per_element = time_per_element;
			pozycjamax = i;
		}
	}
	clock_t t2 = clock();
	double time_spent = (double)(t2 - t1) / CLOCKS_PER_SEC;
	std::cout << "Czas operacji: " << time_spent  << "\n Najdluzsze dodawanie: " << (max_time_per_element/CLOCKS_PER_SEC) << " Obiekt w ktorym to zaszlo: " << pozycjamax << "\n";
	K.to_string();
	system("pause");


	//Tutaj funkcja wyrzuca wyj¹tek 
	K.clear();
	



	return 0;

}


static int rozszerzenie = 2;
template <typename T>
void dynamic_array<T>::size_up()
{
	size = size * rozszerzenie;

	T* tab = new T[size];
	for (int i = 0; i < real_size; i++) {
		tab[i] = start[i];
	}
	delete[] start;
	start = tab;
}
template <typename T>
void dynamic_array<T>::add(T a)
{
	if (real_size == size) {
		size_up();
	}
	start[real_size] = a;
	real_size++;
}
//B
template <typename T>
T dynamic_array<T>::show_status(int i)
{
	return start[i];
}
//D
template <typename T>
void dynamic_array<T>::clear()
{
	delete[] start;
}
//E
template <typename T>
void dynamic_array<T>::to_string()
{
	std::cout << start << " Adres pocz¹tka tablicy";
}
template <typename T>
void dynamic_array<T>::sort()
{
	bool zmiana;
	int temp;
	for (int j = 1; j < real_size - 1; j++) {
		zmiana = false;
		for (int i = 1; i < real_size; i++) {
			if (start[i - 1] > start[i]) {
				temp = start[i - 1];
				start[i - 1] = start[i];
				start[i] = temp;
				zmiana = true;
			}
		}
		if (zmiana) {
			continue;
		}
		else {
			break;
		}
	}

}
//C
template <typename T>
void dynamic_array<T>::replace(int a, T b) {
	start[a] = b;
}

//
template <typename T>
dynamic_array<T>::dynamic_array()
{
}

template <typename T>
dynamic_array<T>::~dynamic_array()
{
	delete[] start;
}