/*
* Лабораторная работа №11
* Обработка произвольных двоичных деревьев
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>

struct Tree {
	int item;
	Tree* right;
	Tree* left;
};
// Корень дерева
Tree* root;
// Указатель на родительскую вершину
Tree* parentVer;
// Признак успешности поиска
bool success;

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
		if (n < 0) {
			std::cout << "Write numbers greater than 0!\n " << std::endl;
			std::cout << "Write again: " << std::endl;
			b = true;
		}
	}

	return n;
}

// Поиск вершины
void lookForVertex(Tree* current, int userItem) {
	if (!success) {
		if (current != NULL) {
			if (current->item == userItem) {
				success = true;
				parentVer = current;
			}
			lookForVertex(current->left, userItem);
			lookForVertex(current->right, userItem);
		}
	}
}

// Создание корня дерева, если он пустой
void createRoot() {
	Tree* r = new Tree;
	std::cout << "Enter a value of the root: " << std::endl;
	int val = checkInput();
	r->item = val;
	r->left = NULL;
	r->right = NULL;
	root = r;
	std::cout << "The root created!" << std::endl;
}

void addVertex_2(int side) {
	Tree* child = new Tree;
	std::cout << "Enter a value for child: " << std::endl;
	int val = checkInput();

	child->item = val;
	child->left = NULL;
	child->right = NULL;
	if (side == 1) {
		parentVer->right = child;
		std::cout << "The right child added!" << std::endl;
	}
	else {
		parentVer->left = child;
		std::cout << "The left child added!" << std::endl;
	}
}

// Добавление вершины в дерево
void addVertex_1() {
	if (root == NULL) { createRoot(); }
	else {
		std::cout << "Enter a value of the parental vertex: " << std::endl;
		int val = checkInput();

		success = false;
		lookForVertex(root, val);

		if (success) {
			// Кол-во потомков
			int q = 0;
			// Правый (1) или левый (2) потомок. По умолчанию правый (это нужно для случая с одним потомком)
			int side = 2;
			// Проверяем число потомков
			if (parentVer->left != NULL) {
				++q;
				side = 1;
			}
			if (parentVer->right != NULL) { ++q; }

			if (q == 2) {
				std::cout << "Adding is impossible. Because the vertex has two child." << std::endl;
			}
			else if (q == 1) {
				std::cout << "One child can be added." << std::endl;
				addVertex_2(side);
			}
			else {
				std::cout << "Two child can be added." << std::endl;
				std::cout << "Do you want to add right child(1) or left(2)?" << std::endl;
				side = checkInput();
				addVertex_2(side);
			}
		}
		else {
			std::cout << "The Vertex didn't found!" << std::endl;
		}
	}
}

// Удаления всего дерева, с помощью обратного обхода
void deleteAllTree(Tree* current) {
	if (current != NULL) {
		deleteAllTree(current->left);
		deleteAllTree(current->right);

		std::cout << "Deleting the vertex - " << current->item << std::endl;
		delete(current);
	}
}

// Вывод в обратно-симметричном порядке
void backSymmetricOutput(Tree* current, int lvl) {
	if (current != NULL) {
		backSymmetricOutput(current->right, lvl + 1);

		std::string str = "     ";
		for (int i = 0; i < lvl; ++i) {
			str += "     ";
		}
		std::cout << str << current->item << std::endl;

		backSymmetricOutput(current->left, lvl + 1);
	}
}

int main()
{
	int command = 1;  // флаг, управляющий интерфейсом

	// не выходим из программы, пока пользователь не захочет этого
	while (command) {

		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\nAdd a new vertex    - 1" << std::endl;
		std::cout << "Delete the tree       - 2" << std::endl;
		std::cout << "Output the tree       - 3" << std::endl;

		bool b2 = true;
		// Цикл, чтобы при введении неправильной команды, запросить ввод заново
		while (b2) {
			b2 = false;

			std::cout << "Enter the command: " << std::endl;

			command = checkInput();

			switch (command) {
			case 1:
				addVertex_1();
				break;

			case 2:
				if (isEmpty()) {
					deleteAllTree(root);
					root = NULL;
				}
				break;

			case 3:
				if (isEmpty()) {
					std::cout << "Tree: " << std::endl;
					backSymmetricOutput(root, 0);
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