#include <limits.h>
#include <stdlib.h>

#include "DoThi.h"
#include "MinHeap.h"

int dijkstra_heap(int n, int start, int end, PhuCan_Item maTranKe[MAX_N][MAX_N], int *maTranKe_size, int *d, int *f)
{
	MIN_HEAP *min_heap = taoMinHeap();

	for (int i = 0; i < n; ++i)
	{
		d[i] = INT_MAX;
		f[i] = 1;
		min_heap->data[i].key = i;
		min_heap->data[i].value = d[i];
		min_heap->key_positions[i] = i;
	}

	d[start] = 0;
	capNhatMinHeap(min_heap, start, d[start]);

	min_heap->size = n;

	while (min_heap->size > 0)
	{
		HEAP_ITEM item = extractTopMinHeap(min_heap);
		int v = item.key;
		if (v == end)
		{
			break;
		}
		f[v] = 0;
		for (int i = 0, n_a = maTranKe_size[v]; i < n_a; ++i)
		{
			PhuCan_Item item = maTranKe[v][i];
			if (f[item.canh] && d[item.canh] > d[v] + item.trongSo)
			{
				d[item.canh] = d[v] + item.trongSo;
				capNhatMinHeap(min_heap, item.canh, d[item.canh]);
			}
		}
	}
	int result = d[end];
	xoaMinHeap(min_heap);
	return result;
}