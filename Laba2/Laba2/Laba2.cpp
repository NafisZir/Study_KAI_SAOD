/*
* Лабораторная работа №2
* Статичекая реализация кольцевой очереди на основе массива.
*/

#include <iostream>
#include <string>

const int SIZE = 5; //Размер массива
int count = 0;      // количество элементов массива

// проверка вводимых значений
int checkInput() {
	int n;
	bool b = true;
	std::string s;

	while (b) {
		b = false;
		try {
			std::cin >> s;
			n = std::stoi(s);
		}
		catch (std::invalid_argument) {
			std::cout << "Only numbers are allowed!\n";
			std::cout << "Write again: " << std::endl;
			b = true;
		}
		catch (std::out_of_range) {
			std::cout << "Too great a value!\n";
			std::cout << "Write again: " << std::endl;
			b = true;
		}
		catch (...) {
			//Если будет выброшено какое-то исключение, которое не обработано выше, то говорим, что возникла неизвестная ошибка
			std::cout << "Unknown error!\n";
			std::cout << "Write again: " << std::endl;
			b = true;
		}
	}

	return n;
}

// Проверка пустоты очереди
bool isEmpty() {
	if (count == 0) {
		std::cout << "Queue is empty!\n" << std::endl;
		return false;
	}
	else
		return true;
}

// Проверка полноты очереди
bool isFull() {
	if (count == SIZE) {
		std::cout << "Queue is full!\n" << std::endl;
		return false;
	}
	else
		return true;
}

// Добавление элемента в очередь
void addItem(int arrQueue[], int last) {
	int item;
	std::cout << "Enter the item: " << std::endl;
	item = checkInput();
	arrQueue[last] = item;
	std::cout << "Item added!\n" << std::endl;
	++count;
}

// Удаление элемента из очереди
void deleteItem(int arrQueue[], int first) {
	arrQueue[first] = NULL;
	std::cout << "Item deleted!\n" << std::endl;
	--count;
}

// Вывод очереди на консоль
void outputQueue(int arrQueue[], int first) {
	if (isEmpty()) {
		std::cout << "\nQueue: " << std::endl;
		for (int i = 0, j = first; i < count; ++i, ++j) {
			if (j == SIZE)
				j = 0;
			std::cout << arrQueue[j] << std::endl;
		}
	}
}

int main()
{
	int first = 0, last = 0; // указатели на начало и конец очереди
	int queue[SIZE];  // массив-очередь
	int command = 1;  // флаг, управляющий интерфейсом

	// не выходим из программы, пока пользователь не захочет этого
	while (command) {
		
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\nCheck queue for emptiness       - 1" << std::endl;
		std::cout << "Check queue for fullness        - 2" << std::endl;
		std::cout << "Adding an item to the queue     - 3" << std::endl;
		std::cout << "Deleting an item from the queue - 4" << std::endl;
		std::cout << "Output queue on the console     - 5" << std::endl;

		bool b2 = true; 
		// Цикл, чтобы при введении неправильной команды, запросить ввод заново
		while (b2) {
			b2 = false;

			std::cout << "Enter the command: " << std::endl;

			command = checkInput();

			switch (command) {

			case 1:
				if (isEmpty())
					std::cout << "Queue is not empty!\n" << std::endl;
				break;

			case 2:
				if (isFull())
					std::cout << "Queue is not full!\n" << std::endl;
				break;

			case 3:
				if (isFull()) {
					addItem(queue, last);
					// Так как очередь кольцевая, то заполняем пустые места в начале, если в конце нет мест
					if (last == SIZE - 1)
						last = 0;
					else
						++last;
				}
				break;

			case 4:
				if (isEmpty()) {
					deleteItem(queue, first);
					// кольцевая очередь
					if (first == SIZE - 1)
						first = 0;
					else
						++first;
				}
				break;

			case 5:
				outputQueue(queue, first);
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