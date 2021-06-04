#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
} list;


// инициализация пустого списка
void init(list *l) {
l->head = NULL;
}

// удалить все элементы из списка
void clean(list *l){
node* del = l->head;
while (del != NULL){
l->head = del->next;
free(del);
del = l->head;
}
}

// проверка на пустоту списка
bool is_empty(list *l){
if (l->head == NULL)
return true;
else return false;
}

// поиск элемента по значению. вернуть NULL если эжемент не найден
node *find(list *l, int value)
{
node* f = l->head;
if (f != NULL){
while ((f != NULL) && (f->value != value))
f = f->next;
}
return f;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value)
{
node* last = (node*)malloc(sizeof(node));
last->value = value;
last->next = NULL;
if (l->head == NULL)
{
l->head = last;
return 0;
}
else {
node* temp = l->head;
while (temp->next != NULL)
temp = temp->next;
temp->next = last;
return 0;
}
return 1;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value){
if (l != NULL)
{
node* first = (node*)malloc(sizeof(node));
first->value=value;
first->next = l->head;
l->head = first;
return 0;
}
return 1;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int value){
if (n != NULL){
node* new_el = (node*)malloc(sizeof(node));
new_el->value = value;
new_el->next = n->next;
n->next = new_el;
return 0;
}
else return 1;
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(list* l, int value) {
	node* nod = find(l, value);
	node* tmp = l->head;
	if (nod == NULL)
		return 1;
	while (tmp != NULL) {
		if (tmp == nod) {
			l->head = tmp->next;
			free(nod);
			return 0;
		}
		else if (tmp->next == nod) {
			tmp->next = tmp->next->next;
			free(nod);
			return 0;
		}
		else tmp = tmp->next;
	}
	return 1;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l){
node* temp = l->head;
while(temp != NULL){
printf("%i ",temp->value);
temp = temp->next;
}
printf("\n");

}


int main() {
 int n;
(void)scanf("%i", &n);
list newlist;
init(&newlist);

int a;
for (int i=0; i<n; i++){
(void)scanf("%i", &a);
push_back(&newlist, a);
}

print(&newlist);

int k[3];
for (int i=0; i<3; i++){
(void)scanf("%i", &k[i]);
}
for (int i=0; i<3; i++){
printf("%i ", (bool)find(&newlist, k[i]));
}

int m;
scanf("%i", &m);
push_back(&newlist, m);

print(&newlist);

int t;
(void)scanf("%i", &t);
push_front(&newlist, t);

print(&newlist);

int j, x;
(void)scanf("%i %i", &j, &x);
node* j_el = newlist.head;
for (int i=1; i<j; i++){
j_el = j_el->next;
}
insert_after(j_el, x);

print(&newlist);

int z;
(void)scanf("%i", &z);
remove_node(&newlist, z);

print(&newlist);

clean(&newlist);

	return 0;
}
