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
void made_vec(std::vector<T>& v) {
	std::for_each(v.begin(), v.end(), [](T& a) {a = rand(); });
}

template<typename T>
void test_sort_time(size_t d, const std::string& type) {
	std::vector<T> v(1000000);
	//заполняем вектор данными, в соответствии с функцией f
	made_vec(v); 
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	start = std::chrono::high_resolution_clock::now();
	//сортировка вектора
	shell_sort(v, d);
	end = std::chrono::high_resolution_clock::now();
	std::cout << type << ", d = " << d << ", time:" << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms;" << std::endl;


}



int main() {
	std::srand(std::time(nullptr));
	
	/*
	made_vec(v1);
	shell_sort(v1, 2);
	*/
	test_sort_time<int>(2, "random");

	return 0;
}
