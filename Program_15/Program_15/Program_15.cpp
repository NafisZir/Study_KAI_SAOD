/*
* Лабораторная работа №15
* Реализовать специальные методы сортировки:
*Простейшую карманную с использованием второго массива и без него
*Обобщенную карманную сортировку с повторяющимися ключами и дополнительными списками
*Поразрядную сортировку
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include <ctime>

int N, qF = 0, qC = 0;
int const RANGE = 100; // Рандомизировать числа от 0 до RANGE - 1
int const QUANTITY_OF_DIGIT = 10;
int const QUANTITY_OF_RANK = 2;

struct List {
	int inf;
	List* next;
};

struct Node {
	List* first;
	List* last;
};

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
	int* arr = new int[N];

	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < N; ++i) {
		arr[i] = rand() % RANGE;
	}

	outputArr(arr);
	return arr;
}

bool check(int lim, int arr[], int num) {
	for (int i = 0; i < lim; i++)
		if (arr[i] == num)
			return 1;
	return 0;
}

// Создание массива с неповторяющимися элементами от 0 до n
int* createSet() {
	int* arr = new int[N];
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		do
		{
			arr[i] = rand() % N;
		} while (check(i, arr, arr[i]));
	}
	std::cout << "Before: ";
	outputArr(arr);
	return arr;
}

void simplePocketSort_WithTwoArrayes(int arr[]) {
	int* rezArr = new int[N];

	for (int i = 0; i < N; ++i) {
		rezArr[arr[i]] = arr[i];
		++qF;
	}
	std::cout << "\nAfter: ";
	outputArr(rezArr);
	outputInf();
}

void simplePocketSort_WithOneArray(int arr[]) {
	int key, temp;

	for (int i = 0; i < N; ++i) {
		++qC;
		while (arr[i] != i) {
			key = arr[i];
			temp = arr[key];
			arr[key] = arr[i];
			arr[i] = temp;
			++qC;
			++qF;
		}
	}
	std::cout << "\nAfter: ";
	outputArr(arr);
	outputInf();
}

void generalPocketSort(int arr[]) {
	List* resArr[RANGE];
	// Инициализация массива списков
	for (int i = 0; i < RANGE; ++i) {
		resArr[i] = NULL;
	}
	// Сортировка
	int key;
	for (int i = 0; i < N; ++i) {
		key = arr[i];

		List *newItem = new List;
		newItem->inf = arr[i];
		newItem->next = resArr[key];
		resArr[key] = newItem;

		++qF;
	}
	// Вывод
	std::cout << "\nAfter: ";
	for (int i = 0, j = 0; i < RANGE; ++i) {
		List *item = resArr[i];

		while (item != NULL) {
			if (j % 20 == 0) {
				std::cout << "\n";
			}
			std::cout << item->inf << " ";
			item = item->next;
			++j;
		}
	}
	outputInf();
}

void clearLists(Node *lists[]) {
	List* temp;
	for (int j = 0; j < QUANTITY_OF_DIGIT; ++j) {
		if (lists[j] != NULL) {
			List* current = lists[j]->first;
			while (current != NULL) {
				temp = current;
				current = current->next;
				temp->next = NULL;
				delete(temp);
			}
			lists[j] = NULL;
		}
	}
}

void updataArray(int arr[], Node *lists[]) {
	int i = 0;
	for (int j = 0; j < QUANTITY_OF_DIGIT; ++j) {
		if (lists[j] != NULL) {
			List* item = lists[j]->first;
			while (item != NULL) {
				arr[i] = item->inf;
				item = item->next;
				++qF;
				++i;
			}
		}
	}
}

void radixSort(int arr[]) {
	Node* arrayOfLists[QUANTITY_OF_DIGIT];
	// Инициализация массива списков
	for (int i = 0; i < QUANTITY_OF_DIGIT; ++i) {
		arrayOfLists[i] = NULL;
	}
	// Сортировка
	int rank, key, k = 0;
	while (k < QUANTITY_OF_RANK) {
		for (int i = 0; i < N; ++i) {
			// Получаем разряд
			int t = 0;
			key = arr[i];
			while (t < k) {
				key = arr[i] / 10;
				++t;
			}
			rank = key % 10;
			// Добавляем в нужный список
			List* item = new List;
			item->inf = arr[i];
			item->next = NULL;
			// Если добавляем первый элемент
			if (arrayOfLists[rank] == NULL) {
				Node* newNode = new Node;
				newNode->first = item;
				newNode->last = item;
				arrayOfLists[rank] = newNode;
			}
			else {
				arrayOfLists[rank]->last->next = item;
				arrayOfLists[rank]->last = item;
			}
			++qF;
		}
		// Сортировка по одному разряду в массиве
		updataArray(arr, arrayOfLists);
		// Очистка спискoB
		clearLists(arrayOfLists);
		++k;
	}
	// Вывод
	std::cout << "\nAfter: ";
	outputArr(arr);
	outputInf();
}

int main()
{
	int command = 1;  // флаг, управляющий интерфейсом
	std::cout << "Enter the size of array: " << std::endl;
	N = checkInput();
	// не выходим из программы, пока пользователь не захочет этого
	while (command) {
		std::cout << "\n-----------------------------------" << std::endl;
		std::cout << "\nThe simple pocket sort with two arrayes       - 1" << std::endl;
		std::cout << "The simple pocket sort with one array         - 2" << std::endl;
		std::cout << "The general pocket sort with lists            - 3" << std::endl;
		std::cout << "The radix sort                                - 4" << std::endl;

		bool b2 = true;
		// Цикл, чтобы при введении неправильной команды, запросить ввод заново
		while (b2) {
			int* a;
			b2 = false;

			std::cout << "Enter the command: " << std::endl;
			command = checkInput();

			switch (command) {
			case 1:
				simplePocketSort_WithTwoArrayes(createSet());
				break;

			case 2:
				simplePocketSort_WithOneArray(createSet());
				break;

			case 3:
				std::cout << "Before: ";
				a = createMainArray();
				generalPocketSort(a);
				break;

			case 4:
				std::cout << "Before: ";
				a = createMainArray();
				radixSort(a);
				break;

			default:
				std::cout << "Wrong command!" << std::endl;
				b2 = true;
			}
		}

		while (true) {
			std::cout << "\nContinue the programm? 1/0" << std::endl;
			command = checkInput();
			if (command == 0 || command == 1) break;
			std::cout << "Wrong command!" << std::endl;
		}
	}
	return 0;
}