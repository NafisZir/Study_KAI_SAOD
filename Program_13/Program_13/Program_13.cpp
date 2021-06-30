/*
* Лабораторная работа №13
* Реализовать программу, объединяющую простейшие методы сортировки массивов:
*сортировку обменом (метод пузырька)
*сортировку выбором
*сортировку вставками
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>

int N;

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
void outputInf(int qF, int qC) {
	std::cout << "\n";
	std::cout << "\nArray has sorted successfully!" << std::endl;
	std::cout << "Quantity of comparisons: " << qC << std::endl;
	std::cout << "Quantity of forwarding: " << qF << std::endl;
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
int* createNewArray() {
	std::cout << "Enter the size of array: " << std::endl;
	N = checkInput();
	int *arr = new int[N];

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

	int qF = 0, qC = 0;
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
	outputInf(qF, qC);
}

// Сортировка вставками
void insertSort(int a[]) {
	int* arr = myCopy(a);

	int qF = 0, qC = 0;
	int temp, j;
	for (int i = 1; i < N; ++i) {
		temp = arr[i];
		j = i - 1;
		++qC;
		while((j>=0) && (temp < arr[j])) {
			arr[j + 1] = arr[j];
			arr[j] = temp;
			--j;
			++qF;
			++qC;
		}
	}
	outputArr(arr);
	outputInf(qF, qC);
}

// Сортировка выбором
void selectionSort(int a[]) {
	int *arr = myCopy(a);

	int qF = 0, qC = 0;
	int min, temp ;
	for (int k = 0; k < N - 1; ++k) {
		min = k;
		for (int i = k + 1; i < N; ++i) {
			if (arr[min] > arr[i]) {
				min = i;
			}
			++qC;
		}

		temp = arr[min];
		arr[min] = arr[k];
		arr[k] = temp;
		++qF;
	}
	outputArr(arr);
	outputInf(qF, qC);
}

int main()
{
	int command = 1;  // флаг, управляющий интерфейсом
	int *arr = createNewArray();
	// не выходим из программы, пока пользователь не захочет этого
	while (command) {
		std::cout << "\n-----------------------------------" << std::endl;
		std::cout << "\nThe bubble sort       - 1" << std::endl;
		std::cout << "The insert sort      - 2" << std::endl;
		std::cout << "The selection sort   - 3" << std::endl;

		bool b2 = true;
		// Цикл, чтобы при введении неправильной команды, запросить ввод заново
		while (b2) {
			b2 = false;
			int val;

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