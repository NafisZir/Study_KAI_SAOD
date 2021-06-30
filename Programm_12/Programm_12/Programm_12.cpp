/*
* Лабораторная работа №12
* Построение и обработка двоичных деревьев поиска
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>

struct Tree {
	int item;
	int counter;
	Tree* right;
	Tree* left;
};
// Корень дерева
Tree* root;
// Указатель на родительскую вершину
Tree* parentVer;

bool b = true;

bool isEmpty() {
	if (root != NULL) {
		return true;
	}
	else {
		std::cout << "Tree is empty!\n" << std::endl;
		return false;
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

// Поиск вершины с заданным значением
Tree* lookForItem(int x) {
	Tree* current = root;
	bool stop = false;

	while (current != NULL && !stop) {
		if (current->item > x) {
			parentVer = current;
			current = current->left;
		}
		else if (current->item < x) {
			parentVer = current;
			current = current->right;
		}
		else {
			stop = true;
		}
	}
	return current;
}

// Рекурсивный метод добавления
Tree* addVertexRec(Tree* current, int x) {
	if (current == NULL) {
		current = new Tree;
		current->left = NULL;
		current->right = NULL;
		current->item = x;
		current->counter = 1;
		if (root == NULL) {
			root = current;
		}
	}
	else {
		if (current->item > x) {
			current->left = addVertexRec(current->left, x);
		}
		else if (current->item < x) {
			current->right = addVertexRec(current->right, x);
		}
		else {
			current->counter++;
		}
	}
	return current;
}

// Нерекурсивный метод добавления
void addVertexNotRec(int x) {
	if (root == NULL) {
		root = new Tree;
		root->item = x;
		root->counter = 1;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		Tree* current = root;
		Tree* parent = NULL;
		while (current != NULL) {
			parent = current;
			if (current->item > x) {
				current = current->left;
			}
			else if (current->item < x) {
				current = current->right;
			}
			else {
                current->counter++;
				current = NULL;
			}
		}
		if (parent->item > x) {
			current = new Tree;
			current->item = x;
			current->counter = 1;
			current->left = NULL;
			current->right = NULL;
			parent->left = current;
		}
		else {
			current = new Tree;
			current->item = x;
			current->counter = 1;
			current->left = NULL;
			current->right = NULL;
			parent->right = current;
		}
	}
}

// Генератор случайного дерева
void randomTree() {
	srand(static_cast<unsigned int>(time(0))); 
	int n = -1;
	while (n <= 0) {
		std::cout << "Enter a quantity of vertexes: " << std::endl;
		n = checkInput();
		for (int i = 0; i < n; i++) {
			root = addVertexRec(root, rand() % 100); 
		}
	}
}

// Находение заменителя
Tree* changer(Tree* p) {
	if (p->right != NULL) {
		changer(p->right);
	}
	else {
		return p;
	}
}

// Удаление заданной вершины
Tree* deleteVertex(Tree* current, int x) {
	if (current == NULL) {
		if (b) {
			std::cout << "This vertex didn't found!" << std::endl;
		}
	}
	else {
		if (current->item > x) {
			current->left = deleteVertex(current->left, x);
		}
		else if (current->item < x) {
			current->right = deleteVertex(current->right, x);
		}
		else {
			if (current->counter > 1) {
				current->counter--;
			}
			else {
				Tree* temp = current;
				if (temp->left == NULL) {
					current = temp->right;
					// Нету потомков
					if (temp->right == NULL) {
						current = NULL;
					}
				}
				else if (temp->right == NULL) {
					current = temp->left;
				}
				// Два потомка
				else {
					Tree* p = changer(current->left);
					// Инициализируем родителя
					lookForItem(p->item);
					// Если p не равен левому потомку current-a
					if (p != current->left) {
						// Так как заменитель точно крайний, то получаем случай "удаления" с одним потомком. Просто меняем указатель родителя
						parentVer->right = p->left;
					}
					
					current->item = p->item;
					current->counter = p->counter;
					// Удаляем заменитель
					b = false;
					current->left = deleteVertex(current->left, p->item);
					temp = p;
					return current;
				}
				delete(temp);
			}
		}
	}
	return current;
}

// Вывод в обратно-симметричном порядке
void backSymmetricOutput(Tree* current, int lvl) {
	if (current != NULL) {
		backSymmetricOutput(current->right, lvl + 1);

		lookForItem(current->item);
		if (parentVer->right == current) {
			std::cout << "\n";
		}
		std::string str = "     ";
		for (int i = 0; i < lvl; ++i) {
			str += "     ";
		}
		std::cout << str << current->item << std::endl;

		backSymmetricOutput(current->left, lvl + 1);
	}
}

// Вывод дерева в линию
void lineOutput(Tree* current) {
	if (current != NULL) {
		lineOutput(current->left);

		std::cout << current->item << "(" << current->counter << ") ";

		lineOutput(current->right);
	}
}

int main()
{
	int command = 1;  // флаг, управляющий интерфейсом

	// не выходим из программы, пока пользователь не захочет этого
	while (command) {

		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\nAdd a new vertex with recursive      - 1" << std::endl;
		std::cout << "Add a new vertex with cycle          - 2" << std::endl;
		std::cout << "Create a random tree                 - 3" << std::endl;
		std::cout << "Delete vertex                        - 4" << std::endl;
		std::cout << "Output tree (back symmetric)         - 5" << std::endl;
		std::cout << "Output tree (line)                   - 6" << std::endl;

		bool b2 = true;
		// Цикл, чтобы при введении неправильной команды, запросить ввод заново
		while (b2) {
			b2 = false;
			int val;

			std::cout << "Enter the command: " << std::endl;

			command = checkInput();

			switch (command) {
			case 1:
				std::cout << "Enter the value: " << std::endl;
				val = checkInput();
				addVertexRec(root, val);
				std::cout << "The Vertex added successfully!" << std::endl;
				break;

			case 2:
				std::cout << "Enter the value: " << std::endl;
				val = checkInput();
				addVertexNotRec(val);
				std::cout << "The Vertex added successfully!" << std::endl;
				break;

			case 3:
				randomTree();
				std::cout << "The tree created successfully!" << std::endl;
				break;

			case 4:
				if (isEmpty()) {
					std::cout << "Enter the value: " << std::endl;
					val = checkInput();
					root = deleteVertex(root, val);
					if (!b) {
						std::cout << "The Vertex deleted successfully!" << std::endl;
					}
					b = true;
				}
				break;

			case 5:
				if (isEmpty()) {
					std::cout << "Tree: " << std::endl;
					backSymmetricOutput(root, 0);
				}
				break;

			case 6:
				if (isEmpty()) {
					std::cout << "Tree: " << std::endl;
					lineOutput(root);
					std::cout << "\n" << std::endl;
				}
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