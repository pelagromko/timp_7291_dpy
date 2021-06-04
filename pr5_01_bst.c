#include <stdio.h>
#include <stdlib.h>


// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node {
	int key;
	struct node* left;
	struct node* right;
	struct node* parent;
} node;


// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree {
	node* root;
	int quantity;
} tree;


// Инициализация дерева
void init(tree* t) {
	t->root = NULL;
	t->quantity = 0;
}

// Удалить все элементы из дерева
void clean(tree* t) {
	node* inter = t->root;
	if (inter != NULL) {
		while (t->quantity != 1) {
			while (inter->left != NULL) {
				inter = inter->left;
			}
			if (inter->right != NULL) inter = inter->right;
			else {
				inter = inter->parent;
				if (inter->left != NULL) {
					free(inter->left);
					inter->left = NULL;
					t->quantity = t->quantity - 1;
				}
				else {
					free(inter->right);
					inter->right = NULL;
					t->quantity = t->quantity - 1;
				}
			}
		}
		free(inter);
		t->root = NULL;
	}
}

// Поиск элемента по значению. Вернуть NULL если элемент не найден
	node* find(tree * t, int value) {
	node* inter = t->root;
	while (inter != NULL) {
		if (inter->key == value) return inter;
		else {
			if (value > inter->key) inter = inter->right;
			else inter = inter->left;
		}
	}
	return inter;
}

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
	int insert(tree* t, int value) {
		node* newNode = (node*)malloc(sizeof(node));
		if (newNode == NULL) return 2;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->key = value;
		if (t->root == NULL) {
			t->root = newNode;
			t->quantity = t->quantity + 1;
			newNode->parent = NULL;
			return 0;
		}
		else {
			node* inter = t->root;
			while (inter != NULL) {
				if (inter->key == value) return 1;
				else if ((newNode->key > inter->key) || (newNode->key < inter->key)) {
					if (newNode->key < inter->key) {
						if (inter->left == NULL) {
							inter->left = newNode;
							newNode->parent = inter;
							t->quantity = t->quantity + 1;
							return 0;
						}
						else inter = inter->left;
					}
					else {
						if (inter->right == NULL) {
							inter->right = newNode;
							newNode->parent = inter;
							t->quantity = t->quantity + 1;
							return 0;
						}
						else inter = inter->right;
					}
				}
			}
		}
	}

	// Удалить элемент из дерева:
	// 0 - удаление прошло успешно
	// 1 - нет элемента с указанным значением
	int remove_node(tree * t, int value) {
		node* inter = find(t, value);
		if (inter == NULL) return 1;

		if ((inter->left == NULL) && (inter->right == NULL)) {
			inter = inter->parent;
			if (inter == NULL) {
				free(t->root);
				t->root = NULL;
				t->quantity = t->quantity - 1;
				return 0;
			}
			if ((inter->left != NULL) && (inter->left->key == value)) {
				free(inter->left);
				inter->left = NULL;
				t->quantity = t->quantity - 1;
				return 0;
			}
			if (inter->right->key == value) {
				free(inter->right);
				inter->right = NULL;
				t->quantity = t->quantity - 1;
			}
		}

		node* inter_parent;
		if (((inter->left == NULL) && (inter->right != NULL)) || ((inter->left != NULL) && (inter->right == NULL))) {
			if ((inter->left == NULL) && (inter->right != NULL)) {
				inter_parent = inter->parent;
				if (inter_parent != NULL) {
					if (inter == inter_parent->right) inter_parent->right = inter->right;
					else inter_parent->left = inter->right;
				}
				else t->root = inter->right;
				inter->right->parent = inter_parent;
				free(inter);
				t->quantity = t->quantity - 1;
				return 0;
			}
			else {
				inter_parent = inter->parent;
				if (inter_parent != NULL) {
					if (inter == inter_parent->right) inter_parent->right = inter->left;
					else inter_parent->left = inter->left;
				}
				else t->root = inter->left;
				inter->left->parent = inter_parent;
				free(inter);
				t->quantity = t->quantity - 1;
				return 0;
			}
		}

		node* two_tree = (node*)malloc(sizeof(node));
		if ((inter->left != NULL) && (inter->right != NULL)) {
			two_tree = inter->right;
			while (two_tree->left != NULL) two_tree = two_tree->left;
			inter->key = two_tree->key;
			if (two_tree->parent->left == two_tree) {
				two_tree->parent->left = two_tree->right;
				if (two_tree->right != NULL) two_tree->right->parent = two_tree->parent;
			}
			else {
				two_tree->parent->right = two_tree->right;
				if (two_tree->right != NULL) two_tree->right->parent = two_tree->parent;
			}
			free(two_tree);
			t->quantity = t->quantity - 1;
			return 0;
		}
	}

	// Удалить минимальный элемент из поддерева, корнем которого является n
	// Вернуть значение удаленного элемента
	int remove_min(node * n) {
		node* temp = n;
		int value;
		while (temp->left != NULL) temp = temp->left;
		value = temp->key;
		temp->parent->left = NULL;
		free(temp);
		return value;
	}

	// Выполнить правое вращение поддерева, корнем которого является n:
	// 0 - успешно выполненная операция
	// 1 - вращение невозможно 
	int rotate_right(tree* t, node * n) {
		if (n == NULL) return 1;
		if (n->left == NULL) return 1;
		if (n->parent != NULL) {
			if (n->parent->right == n) n->parent->right = n->left;
			if (n->parent->left == n) n->parent->left = n->left;
		}
		else t->root = n->left;
		n->left->parent = n->parent;
		n->parent = n->left;
		n->left = n->parent->right;
		if (n->parent->right) n->parent->right->parent = n;
		n->parent->right = n; return 0;
	}

	// Выполнить левое вращение поддерева, корнем которого является n:
	// 0 - успешно выполненная операция
	// 1 - вращение невозможно
	int rotate_left(tree* t, node * n) {
		if (n == NULL) return 1;
		if (n->right == NULL) return 1;
		if (n->parent != NULL) {
			if (n->parent->left == n) n->parent->left = n->right;
			if (n->parent->right == n) n->parent->right = n->right;
		}
		else t->root = n->right;
		n->right->parent = n->parent;
		n->parent = n->right;
		n->right = n->parent->left;
		if (n->parent->left) n->parent->left->parent = n;
		n->parent->left = n;
		return 0;
	}

	int max(node * n) {
		if (n != NULL) {
			int left_m = max(n->left);
			int right_m = max(n->right);
			if (left_m > right_m) return left_m + 1;
			else return right_m + 1;
		}
		else return 0;
	}

	int power(int a, int b) {
		if (b != 0) return a * power(a, b - 1);
		else return 1;
	}

	// Вывести все значения из поддерева, корнем которого является n
	// по уровням начиная с корня.
	// Каждый уровень выводится на своей строке. 
	// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
	// Если дерево пусто, вывести -
	void print(node * n) {
		int quantity;
		quantity = power(2, max(n)) - 1;
		node** list1 = (node**)malloc(sizeof(node*) * quantity);
		list1[0] = n;
		node* tmp;
		int last_empty = 1;
		for (int first = 0; last_empty < quantity; first++) {
			tmp = list1[first];
			if (tmp != NULL) list1[last_empty] = tmp->left;
			else list1[last_empty] = NULL;

			if (tmp != NULL) list1[last_empty + 1] = tmp->right;
			else list1[last_empty + 1] = NULL;
			last_empty = last_empty + 2;
		}
		for (int i = 1; i <= quantity; i *= 2) {
			for (int j = 0; j < i; j++)
				if (list1[i + j - 1] != NULL) printf("%i ", list1[i + j - 1]->key);
				else printf("_ ");
			printf("\n");
		}

		if (n == NULL) printf("- \n");
	}

	// Вывести все значения дерева t, аналогично функции print
	void print_tree(tree * t) {
		if (t->root == NULL) {
			printf("- \n"); return;
		}
		int quantity;
		quantity = power(2, max(t->root)) - 1;
		node** list2 = (node**)malloc(sizeof(node*) * quantity);
		list2[0] = t->root;
		node* tmp;
		int last_empty = 1;
		for (int first = 0; last_empty < quantity; first++) {
			tmp = list2[first];
			if (tmp != NULL) list2[last_empty] = tmp->left;
			else list2[last_empty] = NULL;

			if (tmp != NULL) list2[last_empty + 1] = tmp->right;
			else list2[last_empty + 1] = NULL;
			last_empty = last_empty + 2;
		}
		for (int i = 1; i <= quantity; i *= 2) {
			for (int j = 0; j < i; j++)
				if (list2[i + j - 1] != NULL) printf("%i ", list2[i + j - 1]->key);
				else printf("_ ");
			printf("\n");
		}
	}


	int main() {

		tree newTree;
		init(&newTree);

		int a;
		for (int i = 0; i < 4; i++) {
			scanf("%i", &a);
			insert(&newTree, a);
		}

		print_tree(&newTree);
		printf("\n");

		for (int i = 0; i < 3; i++) {
			scanf("%i", &a);
			insert(&newTree, a);
		}

		print_tree(&newTree);
		printf("\n");

		int m1;
		scanf("%i", &m1);
		node* p_m1 = find(&newTree, m1);
		if (p_m1 == NULL) printf("- ");
		else {
			if (p_m1->parent != NULL) printf("%i ", p_m1->parent->key);
			else printf("_ ");
			if (p_m1->left != NULL) printf("%i ", p_m1->left->key);
			else printf("_ ");
			if (p_m1->right != NULL) printf("%i ", p_m1->right->key);
			else printf("_ ");
		}
		printf("\n\n");

		int m2;
		scanf("%i", &m2);
		node* p_m2 = find(&newTree, m2);
		if (p_m2 == NULL) printf("- ");
		else {
			if (p_m2->parent != NULL) printf("%i ", p_m2->parent->key);
			else printf("_ ");
			if (p_m2->left != NULL) printf("%i ", p_m2->left->key);
			else printf("_ ");
			if (p_m2->right != NULL) printf("%i ", p_m2->right->key);
			else printf("_ ");
		}
		printf("\n\n");

		int m3;
		scanf("%i", &m3);
		remove_node(&newTree, m3);

		print_tree(&newTree);
		printf("\n");

		int result;
		do {
			result = rotate_left(&newTree, newTree.root);
		} while (result == NULL);

		print(newTree.root);
		printf("\n");

		do {
			result = rotate_right(&newTree, newTree.root);
		} while (result == NULL);

		print_tree(&newTree);
		printf("\n");

		printf("%i ", newTree.quantity);
		printf("\n\n");

		clean(&newTree);

		print_tree(&newTree);
		printf("\n");
	}
