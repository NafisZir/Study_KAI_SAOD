/*
* Лабораторная работа №17
* Реализовать метод внутреннего хеширования.
*/

#include <iostream>
#include <cstdlib>
#include <string>

int count = 0, qC = 0;
int const m = 5; // размер хеш-таблицы

std::string table[m];

bool isFull() {
	if (count == m) {
		std::cout << "Array is full." << std::endl;
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

void initTable() {
	for (int i = 0; i < m; ++i) {
		table[i] = "\n";
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
	std::cout << "Quantity of comparisons: " << qC << std::endl;
	std::cout << "\n" << std::endl;
	qC = 0;
}

// Получает ключ от пользователя
std::string getKey() {
	std::string key;
	std::cout << "Enter the key: " << std::endl;
	std::cin >> key;
	return key;
}

// Был ли заданный ключ уже добавлен
int checkKeyInTable(std::string key) {
	int n = key.length();
	int sum = 0;
	// Высчитываем сумму ASCII кода
	for (int i = 0; i < n; ++i) {
		sum += key[i];
	}

	int j = sum % m;
	if (table[j] != key) {
		// Ищем место по формуле
		for (int i = 0; i < m - 3; ++i) {
			j = ((sum % m + i) % m) + 1;
			++qC;
			if (table[j] == key) {
				break;
			}
			j = -1;
		}
	}
	return j;
}

// Вычисляет индекс ключа
int getIndex(std::string key) {
	int n = key.length();
	int sum = 0;
	// Высчитываем сумму ASCII кода
	for (int i = 0; i < n; ++i) {
		sum += key[i];
	}
	// Если ячейка уже занята, то ищем первую пустую по формуле
	int j = sum % m;
	if (table[j] != "\n") {
		for (int i = 0; i < m - 3; ++i) {
			j = ((sum % m + i) % m) + 1;
			++qC;
			if (table[j] == "\n") {
				break;
			}
		}
	}
	return j;
}

// Добавление одного ключа
void addKey() {
	if (isFull()) {
		std::string key = getKey();
		if (checkKeyInTable(key) == -1) {
			qC = 0;
			table[getIndex(key)] = key;
			std::cout << "The key added successfuly!" << std::endl;
			outputInf();
			++count;
		}
		else {
			std::cout << "This key is already in the array!" << std::endl;
		}
	}
}

// Найти заданный ключ
void findKey() {
	if (isEmpty()) {
		std::string key = getKey();
		int i = checkKeyInTable(key);
		if (i != -1) {
			std::cout << "The key found! His index is " << i << std::endl;
			outputInf();
		}
		else {
			std::cout << "The key didn't found! " << std::endl;
		}
	}
}

// Вывод таблицы
void outputTable() {
	if (isEmpty()) {
		std::cout << "Hash-table: " << std::endl;
		for (int i = 0; i < m; ++i) {
			std::cout << i << ") " << table[i];
			if (table[i] != "\n") {
				std::cout << "\n";
			}
		}
	}
}

int main()
{
	int command = 1;  // флаг, управляющий интерфейсом
	initTable();
	// не выходим из программы, пока пользователь не захочет этого
	while (command) {
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Add key              - 1" << std::endl;
		std::cout << "Find the key         - 2" << std::endl;
		std::cout << "Output hash-table    - 3" << std::endl;

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

			default:
				std::cout << "Wrong command!" << std::endl;
				b2 = true;
			}
		}

		while (true) {
			std::cout << "Continue the program? 1/0" << std::endl;
			command = checkInput();
			if (command == 0 || command == 1) break;
			std::cout << "Wrong command!" << std::endl;
		}
	}
	return 0;
}