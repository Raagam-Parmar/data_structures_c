#include "linked_list.h"

void print_int(int value) {
	printf("%d ", value);
}

GEN_LINKED_LIST(int, print_int);

int main() {
	linked_list_int *marks = list_create();

	list_append(marks, 95);
	list_append(marks, 85);
	list_append(marks, 60);
	list_append(marks, 100);

	list_print(marks);
	printf("\n");

	list_destroy(marks);

	return 0;
}