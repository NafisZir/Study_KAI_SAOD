/*
*������������ ������ �5
* ����������� �������� ������ �� ������ ������� � �����������-���������
*/

#include <iostream>
#include <string>

const int SIZE = 4; //������ �������
int count = 0;      // ���������� ��������� �������

struct List {
	int item;
	int next;
};

List* defaultItem = new List;
List* list[SIZE];  // ������-������

void initList() {
	// ��� ������ ������ ���������� -1, ����� ���������
	List* head = new List;
	list[0] = head;
	list[0]->item = NULL;
	list[0]->next = 0;

	defaultItem->next = -1;
	for (int i = 1; i < SIZE; ++i) {
		list[i] = defaultItem;
	}
}

// �������� ������� ������
bool isEmpty() {
	if (count == 0) {
		std::cout << "List is empty!\n" << std::endl;
		return false;
	}
	else
		return true;
}

// �������� ������� ������
bool isFull() {
	if (count == SIZE - 1) {
		std::cout << "List is full!\n" << std::endl;
		return false;
	}
	else
		return true;
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

// ��������� ������ ��� ������ �������� � ��� ���������� � ������
// ��������� ������� �� ��������, ������� ������ ���� �� ������, � ����� ����
void createItem(int iBefore, int iAfter) {
	int element;

	std::cout << "Enter the new item: " << std::endl;
	element = checkInput();

	List* newItem = new List;
	newItem->item = element;
	newItem->next = iAfter;

	// ���� ���� ������ ������, �� ����� ������� ����� ��������� ����
	for (int i = 1; i < SIZE; ++i) {
		if (list[i]->next == -1) {
			list[i] = newItem;
			list[iBefore]->next = i;
			break;
		}
	}
	++count;
}

// ���������� �� ���������
void addBefore() {
	int needItem;

	std::cout << "Before what an element should to add: " << std::endl;
	needItem = checkInput();

	// iBefore ����� �������� ������� ��������, ����� �������� �� ������ ����� �������� ����� �������
	// iCurrent ����� �������� ������� ��������, �� ������� ������ ��������� ����� �������
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

// ���������� ����� ���������
void addAfter() {
	int needItem;

	std::cout << "After what an element should to add: " << std::endl;
	needItem = checkInput();

	// iCurrent ����� �������� ������� ��������, ����� �������� �� ������ ����� �������� ����� �������
	// iAfter ����� �������� ������� ��������, �� ������� ������ ��������� ����� �������
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

// �������, ����������� ���������� ������ ��������
void addItem() {
	int index, needItem;
	int place;
	if (isFull()) {
		//����� ��������� ������ �������
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
				// ������ �������� ���������� ��������� �� � ����� ����������
				int iAfter = list[iCurrent]->next;
				list[iBefore]->next = iAfter;
				// ������ ��������� ����������
				List* oldItem = list[iCurrent];
				// ���������, ��� ��� ������ ����� (������������� ������� -1)
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
	int command = 1;  // ����, ����������� �����������

	initList();
	// �� ������� �� ���������, ���� ������������ �� ������� �����
	while (command) {

		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\nCheck list for emptiness       - 1" << std::endl;
		std::cout << "Check list for fullness        - 2" << std::endl;
		std::cout << "Adding an item to the list     - 3" << std::endl;
		std::cout << "Deleting an item from the list - 4" << std::endl;
		std::cout << "Find the item                  - 5" << std::endl;
		std::cout << "Output list on the console     - 6" << std::endl;

		bool b2 = true;
		// ����, ����� ��� �������� ������������ �������, ��������� ���� ������
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