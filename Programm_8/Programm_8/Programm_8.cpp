/*
* ������������ ������ �8
* ���������� ������ �������
*/

#include <iostream>
#include <string>
#include <Windows.h>

const int MEMORY = 700;

//������ ���������
struct List {
	int item;
	List* head;
	List* next;
};

// ���������� ���������� ���������
List* headM;

//������������� ������
void initMainList() {
	List* h = new List;
	h->next = NULL;
	headM = h;
	std::cout << "Main List created!\n" << std::endl;
}

// �������� ������� �������� ������
bool isEmpty(List *head) {
	if (head->next == NULL) {
		std::cout << "List is empty!\n" << std::endl;
		return false;
	}
	else
		return true;
}

// �������� ������� ������
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

// �������� �������� ��������
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
			//���� ����� ��������� �����-�� ����������, ������� �� ���������� ����, �� �������, ��� �������� ����������� ������
			std::cout << "Unknown error!\n";
			std::cout << "Write again: " << std::endl;
			b = true;
		}
	}

	return n;
}

// ���� �������� ��������������� ������
// ���������� ��������� �� ������, ����������� �� �������
// ��� ��� � ��������� �������� ����� ������ ��
// � � �������� � ������������ ����� ������ next-���
List* lookForItem(List* head, int userItem) {
	List* current = head->next;
	List* before = head;

	while (true) {
		if (current->item == userItem) {
			return before;
		}

		before = current;
		current = current->next;
		if (current == NULL) {
			std::cout << "Item didn't found" << std::endl;
			return NULL;
		}
	}
}

// ��������� ������
void createItem(List* before, List* after, int c) {
	int item;

	std::cout << "Enter a new item: " << std::endl;
	item = checkInput();

	List* newItem = new List;
	newItem->item = item;
	newItem->next = after;
	before->next = newItem;

	if (c == 1) {
		// ������ ��������� ������ ���������������� ������
		List* newList = new List;
		newList->next = NULL;
		newItem->head = newList;
	}
	else {
		newItem->head = NULL;
	}

	std::cout << "Item created!\n" << std::endl;
}

void addBefore(List *head, int c) {
	// ���� ������ ������, �� ���������� "��" �� ��������
	if (isEmpty(head)) {
		int id;

		std::cout << "Before what an item should to add: " << std::endl;
		id = checkInput();

		// before ���������, ����� �������� �� ������ ����� �������� ����� �������
		// before->next ���������, �� ������� ������ ��������� ����� �������
		List* before = lookForItem(head, id);
		if (before != NULL) {
			createItem(before, before->next, c);
		}
	}
}

// ���������� "�����" � ������� ������
void addAfter(List *head, int c) {
	//���� ������ ������, �� ��������� ����� ����� ���������
	if (head->next == NULL) {
		createItem(head, NULL, c);
	}
	else {
		int id;

		std::cout << "After what an item should to add: " << std::endl;
		id = checkInput();

		// before->next ���������, ����� �������� �� ������ ����� �������� ����� �������
		// before->next->next ���������, �� ������� ������ ��������� ����� �������
		List* before = lookForItem(head, id);
		if (before != NULL) {
			createItem(before->next, before->next->next, c);
		}
	}
}

//����������
void addItem(int c) {
	List* head = NULL;
	if (c == 1) {
		head = headM;
	}
	else {
		List* before = NULL;
		while(true){
			int id;
			std::cout << "What list do you want to add a new item: " << std::endl;
			id = checkInput();

			List* before = lookForItem(headM, id);
			if (before != NULL) {
				head = before->next->head;
				break;
			}
		}
	}
	int place;
	if (isFull()) {
		std::cout << "Where to add? Before(1) or after(2) a given element: " << std::endl;
		place = checkInput();

		if (place == 1) {
			addBefore(head, c);
		}
		else {
			addAfter(head, c);
		}
	}
}

// �������� ��������� ��������
void deleteItemCL_2(List* head) {
	if (isEmpty(head)) {
		int needItem;
		std::cout << "what item do you want to delete: " << std::endl;
		needItem = checkInput();

		List* before = lookForItem(head, needItem);
		if (before != NULL) {
			List* temp = before->next;
			// ������ �������� ���������� ��������� �� � ����� ����������
			before->next = before->next->next;

			delete(temp);
			std::cout << "Item deleted!" << std::endl;
		}
	}
}

// ������� ������, � ������� ���������� ������� �������
void deleteItemCL_1() {
	if (isEmpty(headM)) {
		int id;
		std::cout << "From what list do you want to delete item: " << std::endl;
		id = checkInput();

		List* list = lookForItem(headM, id);
		if (list != NULL) {
			deleteItemCL_2(list->next->head);
		}
	}
}

// ������� ��� �������� �� ���������������� ������
void deleteList_2(List* head) {
	if (head->next != NULL) {
		List* current = head->next;
		head->next = NULL;
		while(true){
			List* temp = current;
			current = current->next;
			delete(temp);
			if (current == NULL) { break; }
		}
	}
	delete(head);
}

// ������� �������� ������ � �������� ������
void deleteList_1() {
	if (isEmpty(headM)) {
		int id;
		std::cout << "what list do you want to delete: " << std::endl;
		id = checkInput();

		List* before = lookForItem(headM, id);
		if (before != NULL) {
			List* current = before->next;
			deleteList_2(current->head);
			// ������ ���������
			List* after = current->next;
			before->next = after;
			delete(current);
			std::cout << "The child list deleted!" << std::endl;
		}
	}
}

//����� ����� ����������� �� �����
void outputList() {
	if (isEmpty(headM)) {
		// ������� ����
		List* currentML = headM->next;
		while (true) {
			std::cout << "List " << currentML->item << " : " <<std::endl;

			// ���������� ����
			List* headCL = currentML->head;
			if (isEmpty(headCL)) {
				List* currentCL = headCL->next;
				while (true) {
					std::cout << currentCL->item << std::endl;
					currentCL = currentCL->next;
					if (currentCL == NULL) { break; }
				}
			}

			currentML = currentML->next;
			if (currentML == NULL) { break; }
		}
	}
}

int main()
{
	int command = 1;  // ����, ����������� �����������

	initMainList();
	// �� ������� �� ���������, ���� ������������ �� ������� �����
	while (command) {

		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\nCheck main list for emptiness    - 1" << std::endl;
		std::cout << "Check main list for fullness      - 2" << std::endl;
		std::cout << "Adding an item to the main list   - 3" << std::endl;
		std::cout << "Adding an item to the child list  - 4" << std::endl;
		std::cout << "Delete list from main list        - 5" << std::endl;
		std::cout << "Delete item from child list       - 6" << std::endl;
		std::cout << "Output lists                      - 7" << std::endl;

		bool b2 = true;
		// ����, ����� ��� �������� ������������ �������, ��������� ���� ������
		while (b2) {
			b2 = false;

			std::cout << "Enter the command: " << std::endl;

			command = checkInput();

			switch (command) {
			case 1:
				if (isEmpty(headM))
					std::cout << "List is not empty!\n" << std::endl;
				break;

			case 2:
				if (isFull())
					std::cout << "List is not full!\n" << std::endl;
				break;

			case 3:
				addItem(1);
				break;

			case 4:
				if (isEmpty(headM)) {
					addItem(0);
				}
				break;

			case 5:
				deleteList_1();
				break;

			case 6:
				deleteItemCL_1();
				break;

			case 7:
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