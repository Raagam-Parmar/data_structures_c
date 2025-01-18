#include "../linked_list.h"

void print_float(float value) {
	printf("%f ", value);
}

GEN_LINKED_LIST(float, print_float);

int main() {
	linked_list_float *marks = list_create();

	list_append(marks, 3.1415);
	list_append(marks, 2.7182);
	list_append(marks, 1.6180);
	list_append(marks, 1.1412);

	list_print(marks);
	printf("\n");

	list_destroy(marks);

	return 0;
}