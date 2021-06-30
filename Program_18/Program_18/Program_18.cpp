/*
* Лабораторная работа №18
* Реализовать метод открытого хеширования
*/

#include <iostream>
#include <cstdlib>
#include <string>

int count = 0, qC = 1;
int const m = 5; // размер хеш-таблицы

struct List {
	std::string inf;
	List* next;
};

struct Node {
	List* first;
	List* last;
};

Node *table[m];

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
		table[i] = NULL;
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

// Вывод информации
void outputInf() {
	std::cout << "Quantity of comparisons: " << qC << std::endl;
	std::cout << "\n";
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
	int index = -1;
	if (table[j] != NULL) {
		List* item = table[j]->first;
		while (item != NULL) {
			++qC;
			if (item->inf == key) {
				index = j;
				break;
			}
			item = item->next;
		}
	}
	return index;
}

// Вычисляет индекс ключа
int getIndex(std::string key) {
	int n = key.length();
	int sum = 0;
	// Высчитываем сумму ASCII кода
	for (int i = 0; i < n; ++i) {
		sum += key[i];
	}

	int i = sum % m;
	if (table[i] != NULL) {
		List* item = table[i]->first;
		while (item != NULL) {
			++qC;
			item = item->next;
		}
	}
	return i;
}

// Добавление одного ключа
void addKey() {
	std::string key = getKey();
	if (checkKeyInTable(key) == -1) {
		qC = 1;
		int i = getIndex(key);
		List* newItem = new List;
		newItem->inf = key;
		newItem->next = NULL;

		if (table[i] == NULL) {
			Node* newNode = new Node;
			newNode->first = newItem;
			newNode->last = newItem;
			table[i] = newNode;
		}
		else {
			table[i]->last->next = newItem;
			table[i]->last = newItem;
		}
		std::cout << "The key added successfuly!" << std::endl;
		++count;
		outputInf();
	}
	else {
		std::cout << "This key is already in the array!" << std::endl;
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

void deleteKey() {
	if (isEmpty()) {
		std::cout << "What key do you want to delete?" << std::endl;
		std::string key = getKey();
		if (checkKeyInTable(key) != -1) {
			int i = getIndex(key);
			List* current = table[i]->first;
			List* before = NULL;
			List* after;
			qC = 1;
			// Ищем элемент
			while ((current->inf != key) && (current != NULL)) {
				before = current;
				current = current->next;
			}
			after = current->next;
			// Удаляемый элемент не первый
			if (before != NULL) {
				before->next = after;
				if (after == NULL) {
					table[i]->last = before;
				}
			}
			// Если удаляемый элемент единственный
			else if(after == NULL){
				table[i] = NULL;
			}
			// Если удаляемый элемент первый
			else {
				table[i]->first = after;
			}
			delete(current);
			std::cout << "Key deleted successfuly!" << std::endl;
			--count;
		}
		else {
			std::cout << "Key dont found!" << std::endl;
		}
	}
}

// Вывод таблицы
void outputTable() {
	if (isEmpty()) {
		std::cout << "Hash-table: " << std::endl;
		for (int j = 0; j < m; ++j) {
			if (table[j] != NULL) {
				List* item = table[j]->first;
				std::cout << "Index: " << j << ") "<< std::endl;
				while (item != NULL) {
					std::cout << item->inf << std::endl;
					item = item->next;
				}
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
		std::cout << "\n-----------------------------------" << std::endl;
		std::cout << "Add key              - 1" << std::endl;
		std::cout << "Find the key         - 2" << std::endl;
		std::cout << "Output hash-table    - 3" << std::endl;
		std::cout << "Delete the key       - 4" << std::endl;

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
				deleteKey();
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