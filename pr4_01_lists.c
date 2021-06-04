#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
	struct node *prev;  // ссылка на предыдущий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
	struct node *tail;  // конец списка
} list;


// инициализация пустого списка
void init(list *l){
l->head = NULL;
l->tail = NULL;
}

// удалить все элементы из списка
void clean(list *l){
node* del = l->head;
while (del != NULL){
l->head = del->next;
free(del);
del = l->head;
}
l->tail = NULL;
}

// проверка на пустоту списка
bool is_empty(list *l){
if (l->head == NULL)
return true;
else return false;
}

// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value){
node* f = l->head;
if (f != NULL) {
while ((f != NULL) && (f->value != value))
f = f->next;
}
return f;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value){
if (l != NULL)
{
node* last = (node*)malloc(sizeof(node));
last->value = value;
last->next = NULL;
last->prev = l->tail;
if (last->prev == NULL) l->head = last;
else last->prev->next = last;
l->tail = last;
return 0;
}
return 1;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value){
if (l != NULL)
{
node* first = (node*)malloc(sizeof(node));
first->value = value;
first->prev = NULL;
l->head->prev = first;
first->next = l->head;
l->head = first;
return 0;
}
return 1;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, node *n, int value){
if (n != NULL){
node* new_el = (node*)malloc(sizeof(node));
new_el->value = value;
new_el->next = n->next;
new_el->prev = n;
if (n->next == NULL) l->tail = new_el;
else n->next->prev = new_el;
n->next = new_el;
return 0;
}
else return 1;
}

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, node *n, int value){
if (n!= NULL) {
node* new_el = (node*)malloc(sizeof(node));
new_el->value = value;
new_el->prev = n->prev;
new_el->next = n;
if (n->prev == NULL) l->head = new_el;
else n->prev->next = new_el;
n->prev = new_el;
return 0;
}
else return 1;
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_first(list *l, int value){
node* tmp = l->head;
while (tmp != NULL){
if (tmp->value == value){
if (tmp->next == NULL) l->tail = tmp->prev;
else tmp->next->prev = tmp->prev;
if (tmp->prev == NULL) l->head = tmp->next;
else tmp->prev->next = tmp->next;
free(tmp);
return 0;
}
else tmp = tmp->next;
}
return 1;
}

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list *l, int value){
node* tmp = l->tail;
while (tmp != NULL){
if (tmp->value == value){
if (tmp->prev == NULL) l->head = tmp->next;
else tmp->prev->next = tmp->next;
if (tmp->next == NULL) l->tail = tmp->prev;
else tmp->next->prev = tmp->prev;
free(tmp);
return 0;
}
else tmp = tmp->prev;
}
return 1;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l){
node* temp = l->head;
while (temp != NULL) {
printf("%i ", temp->value);
temp = temp->next;
}
printf("\n");
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l){
node* temp = l->tail;
while (temp != NULL){
printf("%i ", temp->value);
temp = temp->prev;
}
printf("\n");
}


int main() {
int n;
(void)scanf("%i", &n);

list newlist;
init(&newlist);

int a;
for (int i=0; i < n; i++){
(void)scanf("%i", &a);
push_back(&newlist, a);
}

print(&newlist);

int k1, k2, k3;
(void)scanf("%i", &k1);
(void)scanf("%i", &k2);
(void)scanf("%i", &k3);
printf("%i ", (bool)find(&newlist, k1));
printf("%i ", (bool)find(&newlist, k2));
printf("%i ", (bool)find(&newlist, k3));

int m;
(void)scanf("%i", &m);
push_back(&newlist, m);

print_invers(&newlist);

int t;
(void)scanf("%i", &t);
push_front(&newlist, t);

print(&newlist);

int j, x;
(void)scanf("%i %i", &j, &x);
node* j_el = newlist.head;
for (int i=1; i < j; i++){
j_el = j_el->next;
}
insert_after(&newlist, j_el, x);

print_invers(&newlist);

int u, y;
(void)scanf("%i %i", &u, &y);
node* u_el = newlist.head;
for (int i=1; i < u; i++){
u_el = u_el->next;
}
insert_before(&newlist, u_el, y);

print(&newlist);

int z;
(void)scanf("%i", &z);
remove_first(&newlist, z);

print_invers(&newlist);

int r;
(void)scanf("%i", &r);
remove_last(&newlist, r);

print(&newlist);

clean(&newlist);

	return 0;
};
