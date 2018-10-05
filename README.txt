# DataStructure

int x;
DynamicArray dynamicArray;
DataFuncsPointers funcs = {sizeof(int), free, malloc, memcpy, memcmp};

/* 
 * use this functions (free, malloc, memcpy, memcmp) for simple data as int, char, float, struct s{int x;}.
 * creat functions for complex data model as struct c{int i;char * j;}.
 */
 
dtDynamicArrayInit(&dynamicArray, funcs);

x = 7;
dtDynamicArrayAdd(&dynamicArray, &x);

x = 5;
dtDynamicArrayAdd(&dynamicArray, &x);

dtDynamicArraySort(&dynamicArray);
dtDynamicArrayGetFrom(&dynamicArray, &x, 1);
printf("DynamicArray -> %d. member :  %d\n", 1, x);

dtDynamicArrayClear(&dynamicArray);
