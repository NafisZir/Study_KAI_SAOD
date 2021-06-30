/*
* Лабораторная работа №16
* Построить бесконфликтную хеш-таблицу для заданного набора текстовых ключей.
*Число ключей (и размер таблицы) равен 10.
*В качестве ключей взять 10 любых служебных слов языка Паскаль.
*Для преобразования текстовых ключей в числовые значения использовать суммирование кодов символов текстового ключа: код (End) = код (E) + код (n) + код (d).
*Преобразование числового кода ключа в значение индекса выполнить с помощью простейшей хеш-функции, которая берет остаток от целочисленного деления кода на размер хеш-таблицы (в задании – 10).
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include <ctime>

int count = 0, qF = 0, qC = 0;
int const QUAN = 10; // Число ключей и размер массива


std::string table[QUAN];
std::string keys[] = { "TYPE", "CASE", "WITH", "FILE", "Set", "ARRAY", "NOT", "Then", "To", "for" };

// Проверяет все ли ключи уже добавлены
bool isFull() {
	if (count == QUAN) {
		std::cout << "All keys in the array" << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool isEmpty() {
	if (count == 0) {
		std::cout << "Array is empty" << std::endl;
		return false;
	}
	else {
		return true;
	}
}

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
	for (int i = 0; i < QUAN; ++i) {
		if (i % 20 == 0) {
			std::cout << "\n";
		}
		std::cout << arr[i] << " ";
	}
}

// Получает ключ от пользователя
std::string getKey() {
	std::string key;
	std::cout << "Enter the key: " << std::endl;
	std::cin >> key;
	return key;
}

// Проверка соответсвия заданного ключа с одним из исходного набора
bool checkKeyInInitialArr(std::string key) {
	bool b = false;
	for(int i = 0; i < QUAN; ++i) {
		if (key == keys[i]) {
			b = true;
			break;
		}
	}
	if (b != true) {
		std::cout << "This key didn't found in initial set!" << std::endl;
		b = false;
	}
	return b;
}

// Был ли заданный ключ уже добавлен
int checkKeyInTable(std::string key) {
	int index = -1;
	for (int i = 0; i < QUAN; ++i) {
		if (key == table[i]) {
			index = i;
			break;
		}
	}
	return index;
}

// Вычисляет индекс ключа
int getIndex(std::string key) {
	int n = key.length();
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += key[i];
	}
	return sum % QUAN;
}

// Добавление одного ключа
void addKey() {
	if (isFull()) {
		std::string key = getKey();
		if (checkKeyInInitialArr(key)) {
			if (checkKeyInTable(key) == -1) {
				table[getIndex(key)] = key;
				std::cout << "The key added successfuly!" << std::endl;
				++count;
			}
			else {
				std::cout << "This key is already in the array!" << std::endl;
			}
		}
	}
}

// Автоматическое добавление всех элементов в хеш-таблицу
void autoAddKey() {
	if (isFull()) {
		std::string key;
		for (int i = 0; i < QUAN; ++i) {
			key = keys[i];
			if (checkKeyInTable(key) == -1) {
				table[getIndex(key)] = key;
				++count;
			}
		}
		std::cout << "All keys added successfuly!" << std::endl;
	}
}

// Найти заданный ключ
void findKey() {
	if (isEmpty()) {
		std::string key = getKey();
		if (checkKeyInInitialArr(key)) {
			int i = checkKeyInTable(key);
			if (i != -1) {
				std::cout << "The key found! Its index is " << i <<std::endl;
			}
			else {
				std::cout << "The key didn't found! " << std::endl;
			}
		}
	}
}

void deleteKey() {
	if (isEmpty()) {
		std::cout << "What key do you want to delete?" << std::endl;
		std::string key = getKey();
		if (checkKeyInInitialArr(key)) {
			table[getIndex(key)] = "\n";
		}
	}
}

// Вывод таблицы
void outputTable() {
	if (isEmpty()) {
		std::cout << "Hash-table: " << std::endl;
		for (int i = 0; i < QUAN; ++i) {
			std::cout << i << ") " <<table[i] << std::endl;
		}
	}
}

int main()
{
	int command = 1;  // флаг, управляющий интерфейсом

	// не выходим из программы, пока пользователь не захочет этого
	while (command) {
		std::cout << "\n-----------------------------------" << std::endl;
		std::cout << "Keys: " <<keys[0]<<" "<<keys[1]<<" "<<keys[2]<<" "<<keys[3]<<" "<<keys[4]<<" "<<keys[5]<<" "<<keys[6]<<" "<<keys[7]<<" "<<keys[8]<<" "<<keys[9] << std::endl;
		std::cout << "\nAdd key              - 1" << std::endl;
		std::cout << "Find the key         - 2" << std::endl;
		std::cout << "Output hash-table    - 3" << std::endl;
		std::cout << "Auto add             - 4" << std::endl;
		std::cout << "Delete the key       - 5" << std::endl;

		bool b2 = true;
		// Цикл, чтобы при введении неправильной команды, запросить ввод заново
		while (b2) {
			b2 = false;

			std::cout << "Enter the command: " << std::endl;
			command = checkInput();

			switch (command) {
			case 1:
				addKey();
				break;

			case 2:
				findKey();
				break;

			case 3:
				outputTable();
				break;

			case 4:
				autoAddKey();
				break;

			case 5:
				deleteKey();
				break;

			default:
				std::cout << "Wrong command!" << std::endl;
				b2 = true;
			}
		}

		while (true) {
			std::cout << "\nContinue the program? 1/0" << std::endl;
			command = checkInput();
			if (command == 0 || command == 1) break;
			std::cout << "Wrong command!" << std::endl;
		}
	}
	return 0;
}