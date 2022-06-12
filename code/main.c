#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int map[20][20] = {

	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2}};

int end_vertice_x = 20;
int end_vertice_y = 20;

// structures

typedef struct { int x, y, f, g, h, parent_x, parent_y; void* next; } element;

// functions prototypes

void menu(element* open_list, element* closed_list);
void select_start_vertice(element* open_list, element* closed_list);
void quit(element* open_list, element* closed_list);
void display_map(element* open_list, element* closed_list);
element* list_initialization();
void add_vertice(element* list, int x1, int y1);
void delete_element(element* list, int x1, int y1);
int is_a_barrier(int current_vertice_x, int current_vertice_y);
int h_calculation(int x1, int y1);
int is_empty_list(element* list);
int smaller_than(int i);
void astar_algorithm(element* open_list, element* closed_list);
void add_adjacent_vertices(element* open_list, element* closed_list, int x1, int y1);
int is_already_in_the_list(int x1, int y1, element* list);
element* last_element_of_list(element* list);
void display_list(element* list);
int f_calculation(int x1, int y1);
element* minimum_calculation(element* list);
void copy_last_element_of_list_1_to_list_2(element* list_1, element* list_2);
void delete_list(element* list);


// functions

void menu(element* open_list, element* closed_list) {

	system("clear");
	printf("THE DEFAULT START VERTICE COORDINATES ARE [0][0]\n\n");
	printf("SELECT AN ACTION\n\n");
	printf("DISPLAY MAP                <A>\n");
	printf("SELECT A START VERTICE     <B>\n");
	printf("START A* ALGORITHM         <C>\n");
	printf("DISPLAY OPEN LIST          <D>\n");
	printf("DISPLAY CLOSED LIST        <E>\n");
	printf("EXIT THE EXECUTABLE        <F>\n\n");

	char choice = '-';
	scanf("%c", &choice);

	if(choice == 'A' || choice == 'B' || choice == 'C' || choice == 'D') {
		switch(choice) {
			case 'A': display_map(open_list, closed_list); break;
			case 'B': select_start_vertice(open_list, closed_list); break;
			case 'C': astar_algorithm(open_list, closed_list); break;
			case 'D': display_list(open_list); break;
			case 'E': display_list(closed_list); break;
			case 'F': quit(open_list, closed_list); break;
		}
	}
	else menu(open_list, closed_list);

}

// ----------------------------------------------------------------------------------

void select_start_vertice(element* open_list, element* closed_list) {

	system("clear");
	printf("ENTER A X COORDINATE: ");
	int choice_x = -1;
	int choice_y = -1;
	scanf("%d", &choice_x);
	if(choice_x < 0 || 20 < choice_x) select_start_vertice(open_list, closed_list);
	printf("ENTER A Y COORDINATE: ");
	scanf("%d", &choice_y);
	if(choice_y < 0 || 20 < choice_y) select_start_vertice(open_list, closed_list);
	open_list->x = choice_x;
	open_list->y = choice_y;
	menu(open_list, closed_list);

}

// ----------------------------------------------------------------------------------

void quit(element* open_list, element* closed_list) {

	delete_list(open_list);
	delete_list(closed_list);
	free(open_list);
	free(closed_list);
	exit(1);

}

// ----------------------------------------------------------------------------------

void display_map(element* open_list, element* closed_list) {

	system("clear");
	int a = 0;
	printf("  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9  <- COORDINATES\n");
	for(int i = 0; i < 20; i++) {
		if(9 < a) a = 0;
		printf("%d ", a);
		for(int j = 0; j < 20; j++) {
			printf("%d ", map[i][j]);
		}
		a++;
		printf("\n");
	}
	printf("\n");
	printf("BACK     <A>\n\n");
	char choice = '-';
	scanf("%c", &choice);
	if(choice == 'A') {
		switch(choice) {
			case 'A': menu(open_list, closed_list);
		}
	}
	else display_map(open_list, closed_list);

}

// ----------------------------------------------------------------------------------

element* list_initialization() {

	element* list = calloc(1, sizeof(element));
	if(!list) exit(-1);
	list->next = NULL;
	return list;

}

// ----------------------------------------------------------------------------------

void add_vertice(element* list, int x1, int y1) {

	element* new = calloc(1, sizeof(element));
	if((!list) || (!new)) exit(-1);
	new->x = x1;
	new->y = y1;
	new->f = f_calculation(x1, y1);
	new->g = map[x1][y1]++;
	new->h = h_calculation(x1, y1);
	element* pointer_1 = list;
	element* pointer_2 = NULL;
	while(pointer_1->next) {
		pointer_2 = pointer_1->next;
		pointer_1 = pointer_2;
	}
	pointer_1->next = new;

}

// ----------------------------------------------------------------------------------

void delete_element(element* list, int x1, int y1) {


	element* pointer_1 = list;
	element* pointer_2 = NULL;

	while(pointer_1->x != x1 && pointer_1->y != y1) {
		pointer_2 = pointer_1->next;
		pointer_1 = pointer_2;
	}
	element* pointer_3 = pointer_1->next;

	pointer_1 = list;

	while(pointer_1->x != x1 && pointer_1->y != y1) {
		pointer_2 = pointer_1->next;
		pointer_1 = pointer_2;
	}

	int parent_x = pointer_1->parent_x, parent_y = pointer_1->parent_y;

	while(pointer_1->x != parent_x && pointer_1->y != parent_y) {
		pointer_2 = pointer_1->next;
		pointer_1 = pointer_2;
	}

	free(pointer_1->next);
	pointer_1->next = pointer_3;

}

// ----------------------------------------------------------------------------------

int is_a_barrier(int current_vertice_x, int current_vertice_y) {

	if(map[current_vertice_x][current_vertice_y] == 1) return 1;
	else return -1;

}

// ----------------------------------------------------------------------------------

int h_calculation(int x1, int y1) {

	double h;
	h = sqrt((end_vertice_x - x1)*(end_vertice_x - x1) + (end_vertice_y - y1)*(end_vertice_y - y1));
	return (int)h;

}

// ----------------------------------------------------------------------------------

int is_empty_list(element* list) {

	if(!list) return 1;
	else return -1;

}

// ----------------------------------------------------------------------------------

int smaller_than(int i) {

	if ((i - 1) < 0) return 1;
	else return 1;

}

// ----------------------------------------------------------------------------------

void astar_algorithm(element* open_list, element* closed_list) {

	while(last_element_of_list(closed_list)->x != end_vertice_x && last_element_of_list(closed_list)) add_adjacent_vertices(open_list, closed_list, last_element_of_list(closed_list)->x, last_element_of_list(closed_list)->y);

}

// ----------------------------------------------------------------------------------

void add_adjacent_vertices(element* open_list, element* closed_list, int x1, int y1) {

	for(int i = x1 - 1; i <= y1 + 1; i++) {
		if(i < 0 || 20 < i) continue;
		for(int j = y1 - 1; j <= y1 + 1; j++) {
			if(j < 0 || 20 < j) continue;
			if(i == x1 && j == y1) continue;
			if(is_a_barrier(i, j) == 1) continue;
			if(is_already_in_the_list(i, j, open_list) == -1) continue;
			if(is_already_in_the_list(i, j, closed_list) == -1) continue;
			add_vertice(open_list, i, j);
		}
	}

}

// ----------------------------------------------------------------------------------

int is_already_in_the_list(int x1, int y1, element* list) {

	element* tmp = list;

	while(tmp) {
		if(tmp->x != x1 && tmp->y != y1) tmp = tmp->next;
		else if(tmp->x == x1 && tmp->y == y1) return 1;
	}

	return -1;

}

// ----------------------------------------------------------------------------------

element* last_element_of_list(element* list) {

	element* temporarily = list;
	while(temporarily->next) temporarily = temporarily->next;

	return temporarily;

}

// ----------------------------------------------------------------------------------

void display_list(element* list) {

	if(!list) exit(-1);
	element* current = list;
	while (current) {
		printf("coordinates = [%d][%d]\n", current->x, current->y);
		printf("f = %d, ", current->f);
		printf("g = %d, ", current->g);
		printf("h = %d\n", current->h);
		printf("parent = [%d][%d]\n\n", current->parent_x, current->parent_y);
		current = current->next;
	}
	printf("\n");

}

// ----------------------------------------------------------------------------------

int f_calculation(int x1, int y1) {

	int f, g;
	if(map[x1][y1] == 0) g = 1;
	else g = 0;
	f = g + h_calculation(x1, y1);

	return f;

}

// ----------------------------------------------------------------------------------

element* minimum_calculation(element* list) {

	if(!list) exit(1);
	int minimum, i = 0;
	element* tmp = list;
	while(tmp) {
		tmp = tmp->next;
		i++;
	}
	tmp = list->next;
	minimum = tmp->f;
	for(int a = 0; a < i; a++) {
		if(tmp->f < minimum) minimum = tmp->f;
		tmp = tmp->next;
	}
	tmp = list->next;
	while(minimum != tmp->f) {
		tmp = tmp->next;
	}

	return tmp;

}

// ----------------------------------------------------------------------------------

void copy_last_element_of_list_1_to_list_2(element* list_1, element* list_2) {

	element* tmp_1 = list_1;
	element* tmp_2 = list_2;
	while(tmp_1) tmp_1 = tmp_1->next;
	tmp_2->x = tmp_1->x;
	tmp_2->y = tmp_1->y;
	tmp_2->f = tmp_1->f;
	tmp_2->g = tmp_1->g;
	tmp_2->h = tmp_1->h;
	tmp_2->parent_x = tmp_1->parent_x;
	tmp_2->parent_y = tmp_1->parent_y;

}

// ----------------------------------------------------------------------------------

void delete_list(element* list) {

	if(!list) exit(1);
	int i = 0;
	element* tmp = list;
	element* to_delete;
	while(tmp) {
		tmp = tmp->next;
		i++;
	}

	while(i < 0) {
		to_delete = list;
		list = list->next;
		free(to_delete);
		i--;
	}

}

// ----------------------------------------------------------------------------------

int main() {

	system("clear");

	element* open_list = list_initialization();
	open_list->x = 0;
	open_list->y = 0;
	open_list->g = 1;
	open_list->f = f_calculation(open_list->x, open_list->y);
	open_list->h = h_calculation(open_list->x, open_list->y);
	open_list->parent_x = 0;
	open_list->parent_y = 0;
	open_list->next = NULL;

	element* closed_list = list_initialization();
	closed_list->x = 0;
	closed_list->y = 0;
	closed_list->g = 1;
	closed_list->f = f_calculation(closed_list->x, closed_list->y);
	closed_list->h = h_calculation(closed_list->x, closed_list->y);
	closed_list->parent_x = 0;
	closed_list->parent_y = 0;
	closed_list->next = NULL;

	menu(open_list, closed_list);

	void quit(element* open_list, element* closed_list);

	return 1;

}

