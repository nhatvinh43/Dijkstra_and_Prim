#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#define MAX_HEAP_SIZE 50000

typedef struct
{
	int key;
	int value;
} HEAP_ITEM;

typedef struct
{
	int size;
	HEAP_ITEM *data;
	int *key_positions;
} MIN_HEAP;

MIN_HEAP* taoMinHeap(void);

void xoaMinHeap(MIN_HEAP *heap);

HEAP_ITEM extractTopMinHeap(MIN_HEAP *heap);

void capNhatMinHeap(MIN_HEAP *heap, int key, int value);

#endif