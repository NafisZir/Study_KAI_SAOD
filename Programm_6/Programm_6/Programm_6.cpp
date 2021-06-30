/*
* Лабораторная работа №6
* Динамическая реализация списка
* Есть дополнительный стек для хранения удаленных элементов из списка.
*/

#include <iostream>
#include <string>
#include <Windows.h>

const int MEMORY = 700;

struct List {
	int item;
	List* next;
};

// Глобальная переменная заголовок
List* head;
List* headStack;

//Инициализация списка
void initListMain() {
	List* h = new List;
	h->next = NULL;
	head = h;
	std::cout << "List created!\n" << std::endl;
}

void initStack() {
	List* h = new List;
	h = NULL;
	headStack = h;
}

// Проверка пустоты списка
bool isEmpty() {
	if (head->next == NULL) {
		std::cout << "List is empty!\n" << std::endl;
		return false;
	}
	else
		return true;
}

//Проверка пустоты вспомогательного стека
bool isEmptyStack() {
	if (headStack == NULL) {
		std::cout << "Stack is empty!\n" << std::endl;
		return false;
	}
	else
		return true;
}

// Проверка полноты списка
bool isFull() {
	MEMORYSTATUS ms;
	GlobalMemoryStatus(&ms);
	int a;
	a = (int)ms.dwAvailPhys / 1024 / 1024;

	if (a > MEMORY)
		return true;
	else {
		std::cout << "List is full!\n" << std::endl;
		return false;
	}
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

// Выделение памяти для нового элемента и его добавление в список
// Принимает указатели на элементы, которые должны быть до нового, и после него
void createItem(List* before, List* after) {
	int element;

	std::cout << "Enter the new item: " << std::endl;
	element = checkInput();

	List* newItem = new List;
	newItem->item = element;
	newItem->next = after;
	before->next = newItem;

	std::cout << "Item created!\n" << std::endl;
}

// Добавление до заданного
void addBefore() {
	// Если список пустой, то добавление "до" не работает
	if (isEmpty()) {
		int needItem;

		std::cout << "Before what an element should to add: " << std::endl;
		needItem = checkInput();

		// before указатель, после которого мы должны будем добавить новый элемент
		// current указатель, на который должен указывать новый элемент
		List* before = head;
		List* current = before->next;
		while (true) {
			if (current->item == needItem) {
				createItem(before, current);
				break;
			}

			before = current;
			current = before->next;
			if (current == NULL) {
				std::cout << "This item didn't found!: " << std::endl;
				break;
			}
		}
	}
}

// Добавление после заданного
void addAfter() {
	//Если список пустой, то добавляем сразу после заголовка
	if (head->next == NULL) {
		createItem(head, NULL);
	}
	else {
		int needItem;

		std::cout << "After what an element should to add: " << std::endl;
		needItem = checkInput();

		// current указатель, после которого мы должны будем добавить новый элемент
		// after указатель, на который должен указывать новый элемент
		List* current = head->next;
		while (true) {
			if (current->item == needItem) {
				List* after = current->next;
				createItem(current, after);
				break;
			}

			current = current->next;

			if (current == NULL) {
				std::cout << "This item didn't found!: " << std::endl;
				break;
			}
		}
	}
}

// Функция, выполняющая добавление нового элемента
void addItem() {
	int place;
	if (isFull()) {
		std::cout << "Where to add? Before(1) or after(2) a given element: " << std::endl;
		place = checkInput();

		if (place == 1) {
			addBefore();
		}
		else {
			addAfter();
		}
	}
}

void addItemInStack(List* item) {
	if (headStack == NULL) {
		headStack = item;
		headStack->next = NULL;
	}
	else {
		item->next = headStack;
		headStack = item;
	}
}

// Удаление заданного элемента
void deleteItem() {
	if (isEmpty()) {
		List* current;
		List* before;
		int needItem;
		std::cout << "what item do you want to move in stack: " << std::endl;
		needItem = checkInput();

		before = head;
		current = before->next;
		while (true) {
			if (current->item == needItem) {
				// Меняем значения указателей элементов до и после удаленного
				List* after = current->next;
				before->next = after;

				addItemInStack(current);
				std::cout << "Item moved!" << std::endl;
				break;
			}

			before = current;
			current = current->next;

			if (current == NULL) {
				std::cout << "This item didn't found!: " << std::endl;
				break;
			}
		}
	}
}

//Ищем заданный элемент в списке
void lookForItem() {
	if (isEmpty()) {
		int userItem;
		List* nextItem = head;
		std::cout << "Write the item: " << std::endl;
		userItem = checkInput();

		while (true) {
			nextItem = nextItem->next;
			if (nextItem->item == userItem) {
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

//Вывод списка на экран
void outputList() {
	if (isEmpty()) {
		std::cout << "List:" << std::endl;

		List* nextItem = head;
		while(true) {
			nextItem = nextItem->next;

			if (nextItem == NULL) { break; }
			std::cout << nextItem->item << std::endl;
		}
	}
}

//Вывод вспомогательного стека на экран
void outputStack() {
	if (isEmptyStack()) {
		std::cout << "Stack: " << std::endl;
		List* stack = headStack;

		while (stack != NULL) {
			std::cout << stack->item << std::endl;
			stack = stack->next;
		}
	}
}

int main()
{
	int command = 1;  // флаг, управляющий интерфейсом

	initListMain();
	initStack();
	// не выходим из программы, пока пользователь не захочет этого
	while (command) {

		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\nCheck list for emptiness       - 1" << std::endl;
		std::cout << "Check list for fullness        - 2" << std::endl;
		std::cout << "Adding an item to the list     - 3" << std::endl;
		std::cout << "Move an item from the list     - 4" << std::endl;
		std::cout << "Find the item                  - 5" << std::endl;
		std::cout << "Output list on the console     - 6" << std::endl;
		std::cout << "Output stack on the console    - 7" << std::endl;

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

			case 7:
				outputStack();
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