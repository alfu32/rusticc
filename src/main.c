
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "x-vector-char.h"
#include "x-optional.h"
#include "x-vector.h"
#define TRUE 1
#define FALSE 2

OPTIONAL_TYPEDEF(int)
OPTIONAL_DERIVE_PRINT(int, %d)
VECTOR_TYPEDEF(char)
OPTIONAL_TYPEDEF(Vector$char)
OPTIONAL_DERIVE_PRINT(Vector$char, %s)


int optional_test(){
	Optional$int x = {.result = 42, .ok = TRUE};
	print_option_int(x);
	return 0;
}
VECTOR_TYPEDEF(int);
VECTOR_DERIVE_ALLOC(int)
VECTOR_DERIVE_INIT(int)
VECTOR_DERIVE_FREE(int)
VECTOR_DERIVE_PUSH(int)
VECTOR_DERIVE_PRINT(int, %d)
VECTOR_DERIVE_MAP(int)
VECTOR_DERIVE_COPY(int)
VECTOR_DERIVE_CONCAT(int)

int multiplier(int value,int index,Vector$int vec) {
	return value*2+index;
}
int vector_test()
{
	Vector$int v = vector$int_alloc();
	v = vector$int_push(v, 10);
	v = vector$int_push(v, 10);
	v = vector$int_push(v, 10);
	vector$int_print(v);
	Vector$int z=vector$int_init((int[]){1,2,3,4,5,6,7,8,9},9);
	vector$int_print(z);

	v=vector$int_map(v,&multiplier);

	vector$int_print(v);
	Vector$int cp1 = vector$int_copy(v);
	VECTOR_INLINE_FOREACH(index,v,{
		v.buffer[index]=v.buffer[index] - 2;
	})
	vector$int_print(v);
	Vector$int cp2 = vector$int_copy(v);
	Vector$int concat = vector$int_concat(cp1,cp2);
	vector$int_print(concat);
	v=vector$int_free(v);
	vector$int_print(v);
	concat=vector$int_free(concat);
	vector$int_print(concat);
	return 0;
}

int main(const char **argv, int argc)
{
	optional_test();
	vector_test();
	return 0;
}