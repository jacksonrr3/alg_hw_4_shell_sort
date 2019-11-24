#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include <string>

template <typename T>
void shell_sort(std::vector<T>& v, size_t n) {
	for (int gap = v.size() / n; gap > 0; gap /= n) {
		for (int i = 0; i + gap < v.size(); i++) {
			int j = i + gap;
			int tmp = v[j];
			while ((j - gap) >= 0 &&
				v[j - gap] > tmp) {
				v[j] = v[j - gap];
				j -= gap;
			}
			v[j] = tmp;
		}
	}
}

template <typename T>
void made_vec_unsort(std::vector<T>& v) {
	std::for_each(v.begin(), v.end(), [](T& a) {a = rand(); });
}

template <typename T>
void made_vec_10persent(std::vector<T>& v) {
	int n = v.size() / 10;
	for (int i = 0; i < n; i++) {
		v[i] = rand();
	}
}

template <typename T>
void made_vec_5(std::vector<T>& v) {
	int n = v.size() * 5 / 100;
	for (int i = 0; i < 4; i++) {
		v[rand() % v.size()] = rand();
	}
}


template<typename T>
void test_sort_time(size_t g) {
	std::vector<T> v(1000000);
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

	//заполняем вектор слычайными данными
	made_vec_unsort(v);
	start = std::chrono::high_resolution_clock::now();
	//сортировка вектора
	shell_sort(v, g);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Sort unsorted vec, gap = " << g << ", time:" << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms;" << std::endl;

	//10 процентов данных не отсортированы
	made_vec_10persent(v);
	start = std::chrono::high_resolution_clock::now();
	//сортировка вектора
	shell_sort(v, g);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Sort 10 persent unsorted vec, gap = " << g << ", time:" << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms;" << std::endl;

	//5 процентов данных не отсортированы
	made_vec_5(v);
	start = std::chrono::high_resolution_clock::now();
	//сортировка вектора
	shell_sort(v, g);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Sort 5 persent unsorted vec, gap = " << g << ", time:" << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms;" << std::endl;
}



int main() {
	std::srand(std::time(nullptr));

	//тест d=2
	test_sort_time<int>(2);
	// unsorted_vec   =  34264 mc


	//тест d=3
	test_sort_time<int>(3);

	//тест d=4
	test_sort_time<int>(4);

	//тест d=5
	test_sort_time<int>(5);

	//тест d=6
	test_sort_time<int>(6);

	//тест d=7
	test_sort_time<int>(7);

	//		d(gap) =      2	           3           4
	// unsorted_vec   	=  34264ms 	30380ms	    33521ms
	// unsort_10_persent	=  22380ms 	21594ms	    19301ms	
	// unsort_5_persent	=  18862ms	19713ms     18686ms

	return 0;
}
