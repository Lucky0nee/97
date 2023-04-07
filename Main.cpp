#include <iostream>
#include <vector>
#include <map>

typedef std::vector<long long int> vector;

constexpr long long int NSK_R(long long int num1, long long int num2, long long int i = 1) {
	if (num1 == 0 || num2 == 0)
		return 0;

	if (i % num1 == 0 && i % num2 == 0) return i;
	else return NSK_R(num1, num2, ++i);
}

constexpr long long int NSD_R(long long int num1, long long int num2, long long int i) {
	if (num1 == 0 || num2 == 0)
		return 1;

	if (num1 % i == 0 && num2 % i == 0) return i;
	else return NSD_R(num1, num2, --i);
}

bool findNumber(vector _vector, long long int number, long long int& index) {
	for (long long int i = 0; i < _vector.size(); i++) {
		if (_vector[i] == number) {
			index = i;
			return true;
		}
	}

	return false;
}

void DeleteElementFromVector(vector& vec, long long int index) {
	if (vec.size() <= 0 || vec.size() == index)
		return;

	for (int i = 0; i < vec.size(); i++) {
		if (i >= index) {
			vec[i] = vec[i + 1];
		}
	}

	vec.pop_back();
	return;
}

void caclulate(vector& _vector, long long int number) {
	for (long long int j = 2; j < number + 2; j++) {
		if (number == 1) break;

		if (number % j == 0) {
			number /= j;
			_vector.push_back(j);
			j--;
		}
	}
}

int NSD(long long int num1, long long int num2) {
	 if (num1 == 0 || num2 == 0)
		 return 1;

	vector vec1, vec2, vec3;

	num1 = abs(num1);
	num2 = abs(num2);

	caclulate(vec1, num1);
	caclulate(vec2, num2);

	for (long long int j = 2; j < (num2 > num1 ? num2 : num1) + 2; j++) {
		long long int index1, index2;
		if (findNumber(vec1, j, index1)) {
			if (findNumber(vec2, j, index2)) {
				vec3.push_back(j);
				DeleteElementFromVector(vec1, index1);
				DeleteElementFromVector(vec2, index2);
				j--;
			}
		}
	}

	long long int sum = 1;

	for (long long int i = 0; i < vec3.size(); i++) {
		sum *= vec3[i];
	}

	return sum;
}
long long int NSK(long long int num1, long long int num2) {
	if (num1 == 0 || num2 == 0)
		return 0;

	return abs(num1 * num2) / NSD(num1, num2);
}

double R(long long int number1, long long int number2) {
	double time_spent = 0.0;
	clock_t begin = clock();

	std::cout << "NSD (recursive) number : " << NSD_R(number1, number2, (number2 < number1 ? number1 : number2)) << "\n";
	std::cout << "NSK (recursive) number : " << NSK_R(number1, number2) << "\n";
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	//std::cout << "The elapsed time is " << time_spent << " seconds" << "\n\n";
	return time_spent;
}
double I(long long int number1, long long int number2) {
	double time_spent = 0.0;
	clock_t begin = clock();

	std::cout << "NSD number : " << NSD(number1, number2) << "\n";
	std::cout << "NSK number : " << NSK(number1, number2) << "\n";

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	//std::cout << "The elapsed time is " << time_spent << " seconds" << "\n\n";
	return time_spent;
}

void mapToVector(std::map<long int, long int> map, vector &vec1, vector &vec2) {
	for (std::pair<long int, int> str : map) {
		vec1.push_back(str.first);
		vec2.push_back(str.second);
	}
}

int main() {
	srand(time(NULL));

	std::map<long int, long int> map;
	vector vec1, vec2;

	for (long int index = 0; index < 200; index++) {
		map[(rand() % 1000) * 100] = (rand() % 10) * 100;
	}

	double iSum = 0;
	double rSum = 0;

	mapToVector(map, vec1, vec2);

	for (int index = 0; index < map.size(); index++) {
		std::cout << "num1 = " << vec1[index] << "\n";
		std::cout << "num2 = " << vec2[index] << "\n";

		double i = I(vec1[index], vec2[index]);
		double r = R(vec1[index], vec2[index]);

		iSum += i;
		rSum += r;

		std::cout << "\n";
	}

	if (iSum > rSum) {
		std::cout << rSum << " vs " << iSum << "\n";
		std::cout << "Recursive method is faster \n";
	}
	else if (iSum < rSum) {
		std::cout << iSum << " vs " << rSum << "\n";
		std::cout << "Iterative method is faster \n";
	}

/*
test #1
8000
99999
Iterative method is faster

test #2
80000000
50000000
Recursive method is faster
*/

	return EXIT_SUCCESS;
}

/*
Написати рекурсивну функцію обчислення найбільшого спільного дільника двох цілих чисел.
А також функцію для обчислення найменшого спільного кратного.

Написати ітераційну функцію функцію обчислення найбільшого спільного дільника двох цілих чисел.
А також функцію для обчислення найменшого спільного кратного.

Сворити контейнер з великої кількості пар різних цілих чисел. 
Застосувати по черзі ітераційні і рекурсивні функції до цих пар чисел. 
Визначити час виконання кожної з них.
*/
