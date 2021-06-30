/*
* Лабораторная работа №14
* Реализовать улучшенные методы сортировки:
* метод Шелла
* быстрая сортировка
* пирамидальная сортировка
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>

int N, qF = 0, qC = 0;
int steps[] = { 1, 3, 5, 9, 17, 33, 65, 129, 257, 513, 1025, 2049, 4097, 8194 }; // последовательность шагов

// проверка вводимых значений
int checkInput() {
	int n;
	std::string s;

	while (true) {
		try {
			std::cin >> s;
			n = std::stoi(s);
		}
		catch (std::invalid_argument) {
			std::cout << "Only numbers are allowed!\n";
			std::cout << "Write again: " << std::endl;
			continue;
		}
		catch (std::out_of_range) {
			std::cout << "Too great a value!\n";
			std::cout << "Write again: " << std::endl;
			continue;
		}
		catch (...) {
			//Если будет выброшено какое-то исключение, которое не обработано выше, то говорим, что возникла неизвестная ошибка
			std::cout << "Unknown error!\n";
			std::cout << "Write again: " << std::endl;
			continue;
		}
		if (n < 0) {
			std::cout << "Write numbers greater than 0!\n " << std::endl;
			std::cout << "Write again: " << std::endl;
			continue;
		}
		break;
	}
	return n;
}

// Копировании массива
int* myCopy(int a[]) {
	int* arr = new int[N];
	for (int i = 0; i < N; ++i) {
		arr[i] = a[i];
	}

	return arr;
}

// Вывод информации по сортировке
void outputInf() {
	std::cout << "\n";
	std::cout << "\nArray has sorted successfully!" << std::endl;
	std::cout << "Quantity of comparisons: " << qC << std::endl;
	std::cout << "Quantity of forwarding: " << qF << std::endl;
	qF = qC = 0;
}

// Вывод содержимого массива
void outputArr(int arr[]) {
	for (int i = 0; i < N; ++i) {
		if (i % 20 == 0) {
			std::cout << "\n";
		}
		std::cout << arr[i] << " ";
	}
}

// Создание рандомного массива
int* createMainArray() {
	std::cout << "Enter the size of array: " << std::endl;
	N = checkInput();
	int* arr = new int[N];

	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < N; ++i) {
		arr[i] = rand() % 100;
	}

	outputArr(arr);
	return arr;
}

// Сортировка обменом (пузырьком)
void bubleSort(int a[]) {
	int* arr = myCopy(a);

	int temp;
	for (int i = 0; i < N; ++i) {
		for (int j = N - 1; j >= i; --j) {
			if (arr[j] < arr[j - 1]) {
				temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
				++qF;
			}
			++qC;
		}
	}
	outputArr(arr);
	outputInf();
}

// Сортировка вставками
void insertSort(int a[]) {
	int* arr = myCopy(a);

	int temp, j;
	for (int i = 1; i < N; ++i) {
		temp = arr[i];
		j = i - 1;
		++qC;
		while ((j >= 0) && (temp < arr[j])) {
			arr[j + 1] = arr[j];
			arr[j] = temp;
			--j;
			++qF;
			++qC;
		}
	}
	outputArr(arr);
	outputInf();
}

// Сортировка выбором
void selectionSort(int a[]) {
	int* arr = myCopy(a);

	int min, temp;
	for (int k = 0; k < N - 1; ++k) {
		min = arr[k];
		temp = k;
		for (int i = k + 1; i < N; ++i) {
			if (min > arr[i]) {
				min = arr[i];
				temp = i;
				++qF;
			}
			++qC;
		}
		arr[temp] = arr[k];
		arr[k] = min;
	}
	outputArr(arr);
	outputInf();
}

// Метод Шелла
void methodShell(int a[]) {
	int* arr = myCopy(a);

	int temp, j, k, t;
	t = (log(N) / log(2) - 1);
	// t - число шагов группировки
	// m - номер шага
	// к - кол-во элементов в группе
	for (int m = t - 1; m >= 0; --m) {
		k = steps[m];
		for (int i = k; i < N; ++i) {
			j = i - k;
			temp = arr[i];
			++qC;
			while ((j >= 0) && (temp < arr[j])) {
				arr[j + k] = arr[j];
				arr[j] = temp;
				j -= k;
				++qF;
				++qC;
			}
		}
	}
	outputArr(arr);
	outputInf();
}

// Быстрая сортировка
int* quickSort(int left, int right, int arr[]) {
	int i, j, mid, temp;

	i = left;
	j = right;
	mid = arr[(left + right) / 2];
	
	while (i <= j) {
		while (arr[i] < mid) {
			++i;
			++qC;
		}
		++qC;
		while (arr[j] > mid) {
			--j;
			++qC;
		}
		++qC;
		if (i <= j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			++i;
			--j;
			++qF;
		}
	}

	if (left < j) {
		quickSort(left, j, arr);
	}
	if (i < right) {
		quickSort(i, right, arr);
	}
	
	return arr;
}

// Создание массива-пирамиды, просеивание
void sito(int l, int right, int* arr) {
	int r = 2 * l, temp = arr[l];
	
	++qC;
	// Выбираем минимальный
	if ((r < right) && (arr[r + 1] > arr[r]))
		++r;
	++qC;
	while ((r <= right) && (arr[r] > temp)) {
		arr[l] = arr[r];
		arr[r] = temp;
		l = r;
		r = 2 * l;
		++qC;
		if ((r < right) && (arr[r + 1] > arr[r]))
			r++;
		++qC;
		++qF;
	}
}

// Сортировка пирамидой
void pyramidalSort(int a[]) {
	int* arr = myCopy(a);
	int left = N / 2;
	int right = N - 1;
	int temp;

	while (left > 0) {
		--left;
		sito(left, right, arr);
	}
	
	while (right > 0) {
		temp = arr[0];
		arr[0] = arr[right];
		arr[right] = temp;
		++qF;
		--right;
		sito(left, right, arr);
	}
	outputArr(arr);
	outputInf();
}

int main()
{
	int command = 1;  // флаг, управляющий интерфейсом
	int* arr = createMainArray();
	// не выходим из программы, пока пользователь не захочет этого
	while (command) {
		std::cout << "\n-----------------------------------" << std::endl;
		std::cout << "\nThe bubble sort      - 1" << std::endl;
		std::cout << "The insert sort      - 2" << std::endl;
		std::cout << "The selection sort   - 3" << std::endl;
		std::cout << "The method Shell     - 4" << std::endl;
		std::cout << "The quick sort       - 5" << std::endl;
		std::cout << "The pyramidal sort   - 6" << std::endl;

		bool b2 = true;
		// Цикл, чтобы при введении неправильной команды, запросить ввод заново
		while (b2) {
			b2 = false;
			int val;
			int* a;

			std::cout << "Enter the command: " << std::endl;
			command = checkInput();

			switch (command) {
			case 1:
				bubleSort(arr);
				break;

			case 2:
				insertSort(arr);
				break;

			case 3:
				selectionSort(arr);
				break;

			case 4:
				methodShell(arr);
				break;

			case 5:
				a = myCopy(arr);
				a = quickSort(0, N - 1, a);
				outputArr(a);
				outputInf();
				break;

			case 6:
				pyramidalSort(arr);
				break;

			default:
				std::cout << "Wrong command!" << std::endl;
				b2 = true;
			}
		}

		while (true) {
			std::cout << "Continue the programm? 1/0" << std::endl;
			command = checkInput();
			if (command == 0 || command == 1) break;
			std::cout << "Wrong command!" << std::endl;
		}
	}
	return 0;
}