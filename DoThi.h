#ifndef DOTHI_H
#define DOTHI_H
#define MAX_N 10000
#include <limits.h>
typedef struct {
	int canh;
	int trongSo;
} PhuCan_Item;

int prim(int n, PhuCan_Item maTranKe[MAX_N][MAX_N],
	int *maTranKe_size, int *d, int *f);

int prim_heap(int n, PhuCan_Item maTranKe[MAX_N][MAX_N],
	int *maTranKe_size, int *d, int *f);

int dijkstra(int n, int batDau, int ketThuc, PhuCan_Item maTranKe[MAX_N][MAX_N],
	int *maTranKe_size, int *d, int *f);

int dijkstra_heap(int n, int batDau, int ketThuc, PhuCan_Item maTranKe[MAX_N][MAX_N],
	int *maTranKe_size, int *d, int *f);
#endif