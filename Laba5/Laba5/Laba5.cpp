/*
*Лабораторная работа №5
* Реализовать линейный список на основе массива с указателями-индексами
*/

#include <iostream>
#include <string>

const int SIZE = 4; //Размер массива
int count = 0;      // количество элементов массива

struct List {
	int item;
	int next;
};

List* defaultItem = new List;
List* list[SIZE];  // массив-список

void initList() {
	// Все пустые ячейки помечаются -1, кроме заголовка
	List* head = new List;
	list[0] = head;
	list[0]->item = NULL;
	list[0]->next = 0;

	defaultItem->next = -1;
	for (int i = 1; i < SIZE; ++i) {
		list[i] = defaultItem;
	}
}

// Проверка пустоты списка
bool isEmpty() {
	if (count == 0) {
		std::cout << "List is empty!\n" << std::endl;
		return false;
	}
	else
		return true;
}

// Проверка полноты списка
bool isFull() {
	if (count == SIZE - 1) {
		std::cout << "List is full!\n" << std::endl;
		return false;
	}
	else
		return true;
}

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

// Выделение памяти для нового элемента и его добавление в массив
// Принимает индексы на элементы, которые должны быть до нового, и после него
void createItem(int iBefore, int iAfter) {
	int element;

	std::cout << "Enter the new item: " << std::endl;
	element = checkInput();

	List* newItem = new List;
	newItem->item = element;
	newItem->next = iAfter;

	// Если есть пустая ячейка, то новый элемент будет указывать туда
	for (int i = 1; i < SIZE; ++i) {
		if (list[i]->next == -1) {
			list[i] = newItem;
			list[iBefore]->next = i;
			break;
		}
	}
	++count;
}

// Добавление до заданного
void addBefore() {
	int needItem;

	std::cout << "Before what an element should to add: " << std::endl;
	needItem = checkInput();

	// iBefore имеет значение индекса элемента, после которого мы должны будем добавить новый элемент
	// iCurrent имеет значение индекса элемента, на который должен указывать новый элемент
	int iBefore = 0, iCurrent = list[0]->next;
	while (true) {
		if (list[iCurrent]->item == needItem) {
			createItem(iBefore, iCurrent);
			break;
		}

		iBefore = iCurrent;
		iCurrent = list[iCurrent]->next;
		if (iCurrent == NULL) {
			std::cout << "This item didn't found!: " << std::endl;
			break;
		}
	}
}

// Добавление после заданного
void addAfter() {
	int needItem;

	std::cout << "After what an element should to add: " << std::endl;
	needItem = checkInput();

	// iCurrent имеет значение индекса элемента, после которого мы должны будем добавить новый элемент
	// iAfter имеет значение индекса элемента, на который должен указывать новый элемент
	int iCurrent = list[0]->next;
	while (true) {
		if (list[iCurrent]->item == needItem) {
			int iAfter = list[iCurrent]->next;
			createItem(iCurrent, iAfter);
			break;
		}
		
		iCurrent = list[iCurrent]->next;

		if (iCurrent == NULL) {
			std::cout << "This item didn't found!: " << std::endl;
			break;
		}
	}
}

// Функция, выполняющая добавление нового элемента
void addItem() {
	int index, needItem;
	int place;
	if (isFull()) {
		//Когда добавляем первый элемент
		if (count == 0) {
			createItem(0, NULL);
		}
		else {
			std::cout << "Where to add? Before(1) or after(2) a given element: " << std::endl;
			place = checkInput();
			if (place == 1) {
				addBefore();
			}
			else{
				addAfter();
			}
		}
	}
}

void deleteItem() {
	if (isEmpty()) {
		int iCurrent, iBefore;
		int needItem;
		std::cout << "what item do you want to delete: " << std::endl;
		needItem = checkInput();

		iBefore = 0;
		iCurrent = list[0]->next;
		while (true) {
			if (list[iCurrent]->item == needItem) {
				// Меняем значения указателей элементов до и после удаленного
				int iAfter = list[iCurrent]->next;
				list[iBefore]->next = iAfter;
				// Создаём временную переменную
				List* oldItem = list[iCurrent];
				// Указываем, что это ячейка пуста (устанавливаем значени -1)
				list[iCurrent] = defaultItem;
				delete(oldItem);
				std::cout << "Item deleted!" << std::endl;
				--count;
				break;
			}
			
			iBefore = iCurrent;
			iCurrent = list[iCurrent]->next;
			if (iCurrent == NULL) {
				std::cout << "This item didn't found!: " << std::endl;
				break;
			}
		}
	}
}

void lookForItem() {
	if (isEmpty()) {
		int userItem;
		int nextItem = 0;
		std::cout << "Write the item: " << std::endl;
		userItem = checkInput();

		while (true) {
			nextItem = list[nextItem]->next;
			if (list[nextItem]->item == userItem) {
				std::cout << "Item found" << std::endl;
				break;
			}

			if (nextItem == NULL) {
				std::cout << "Item didn't found" << std::endl;
				break;
			}
		}
	}
}

void outputList() {
	if(isEmpty()) {
		std::cout << "List:" << std::endl;
		int nextItem = 0;
		for (int i = 0; i < count; ++i) {
			nextItem = list[nextItem]->next;
			std::cout << list[nextItem]->item << std::endl;
		}
	}
}

int main()
{
	int command = 1;  // флаг, управляющий интерфейсом

	initList();
	// не выходим из программы, пока пользователь не захочет этого
	while (command) {

		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\nCheck list for emptiness       - 1" << std::endl;
		std::cout << "Check list for fullness        - 2" << std::endl;
		std::cout << "Adding an item to the list     - 3" << std::endl;
		std::cout << "Deleting an item from the list - 4" << std::endl;
		std::cout << "Find the item                  - 5" << std::endl;
		std::cout << "Output list on the console     - 6" << std::endl;

		bool b2 = true;
		// Цикл, чтобы при введении неправильной команды, запросить ввод заново
		while (b2) {
			b2 = false;

			std::cout << "Enter the command: " << std::endl;

			command = checkInput();

			switch (command) {
			case 1:
				if (isEmpty())
					std::cout << "List is not empty!\n" << std::endl;
				break;

			case 2:
				if (isFull())
					std::cout << "List is not full!\n" << std::endl;
				break;

			case 3:
				addItem();
				break;

			case 4:
				deleteItem();
				break;
		
			case 5:
				lookForItem();
				break;
			case 6:
				outputList();
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