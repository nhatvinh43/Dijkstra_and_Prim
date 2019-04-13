#include "DoThi.h"
#include "MinHeap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX_N 10000
PhuCan_Item maTranKe[MAX_N][MAX_N];
int maTranKe_size[MAX_N], d[MAX_N], visited[MAX_N];
int checkConnect[MAX_N][MAX_N];
int pathList[MAX_N];

int Create(PhuCan_Item maTranKe[MAX_N][MAX_N],int checkConnect[MAX_N][MAX_N], int  maTranKe_size[MAX_N], int canh1, int canh2, int trongSo)
{

	if (checkConnect[canh1][canh2] != 0 || checkConnect[canh2][canh1] != 0)
	{
		return 0;
	}
	else
	{
		maTranKe[canh1][maTranKe_size[canh1]].canh = canh2;
		maTranKe[canh1][maTranKe_size[canh1]].trongSo = trongSo;
		maTranKe_size[canh1]++;
		checkConnect[canh1][canh2] = 1;

		maTranKe[canh2][maTranKe_size[canh2]].canh = canh1;
		maTranKe[canh2][maTranKe_size[canh2]].trongSo = trongSo;
		maTranKe_size[canh2]++;
		checkConnect[canh2][canh1] = 1;
	}
	return 1;
}

int Delete(PhuCan_Item maTranKe[MAX_N][MAX_N], int checkConnect[MAX_N][MAX_N], int  maTranKe_size[MAX_N], int canh1, int canh2)
{
	if (checkConnect[canh1][canh2] == 0 || checkConnect[canh2][canh1] == 0)
	{
		return 0;
	}
	else
	{
		maTranKe[canh1][maTranKe_size[canh1]].canh = -1;
		maTranKe[canh1][maTranKe_size[canh1]].trongSo = 0;
		maTranKe_size[canh1]--;
		checkConnect[canh1][canh2] = 0;

		maTranKe[canh2][maTranKe_size[canh2]].canh = -1;
		maTranKe[canh2][maTranKe_size[canh2]].trongSo = 0;
		maTranKe_size[canh2]--;
		checkConnect[canh2][canh1] = 0;
		return 1;
	}
}

int ShortestPath_Find(int n, int start, int end, PhuCan_Item maTranKe[MAX_N][MAX_N], int *maTranKe_size, int *d, int *f, int* pathList)
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
	int count = 1;
	while (min_heap->size > 0)
	{
		HEAP_ITEM item = extractTopMinHeap(min_heap);
		int v = item.key;
		if (v == end)
		{
			break;
		}
		pathList[count] = v + 1;
		count++;
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
	pathList[0] = count;
	pathList[count] = end+1;
	int result = d[end];
	xoaMinHeap(min_heap);
	if (result == 0)
	{
		return -1;
	}
	return result;
}

void docFile(PhuCan_Item maTranKe[MAX_N][MAX_N], int checkConnect[MAX_N][MAX_N], int *maTranKe_size, int *d, int *f,int* pathList)
{
	for (int i = 0; i < MAX_N; i++)
	{
		maTranKe_size[i] = 0;
	}
	int DinhCount = 0;
	int CanhCount = 0;
	fstream fp("input.txt", ios::in);
	fstream fp2("output.txt", ios::out);
	string tempString;
	while (!fp.eof())
	{
		fp >> tempString;
		if (tempString == "CREATE" || tempString == "create" || tempString == "Create")
		{	
			int i, j, trongSo;
			fp >> i >> j >> trongSo;
			i--;
			j--;
			int result = Create(maTranKe, checkConnect, maTranKe_size, i, j, trongSo);
			if (result == 1)
			{
				DinhCount = 0;
				CanhCount = 0;
				for (int k = 0; k < MAX_N; k++)
				{
					if (maTranKe_size[k] != 0 && DinhCount <= k)
					{
						DinhCount = k+1;
					}
				}
				CanhCount++;
			}
			fp2 << result << endl;
		}
		if (tempString == "DELETE" || tempString == "delete" || tempString == "Delete")
		{			
			int i, j;
			fp >> i >> j;
			i--;
			j--;
			int result = Delete(maTranKe,checkConnect, maTranKe_size, i, j);
			if (result == 1)
			{
				DinhCount = 0;
				CanhCount = 0;
				for (int k = 0; k < MAX_N; k++)
				{
					if (maTranKe_size[k] != 0 && DinhCount <= k+1)
					{
						DinhCount = k + 1;
					}
				}
				CanhCount--;
			}
			fp2 << result << endl;
			for (int i = 0; i < DinhCount; i++)
			{
				for (int j = DinhCount - 1; j < DinhCount; j++)
				{
					maTranKe[i][j].canh = -1;
					maTranKe[i][j].trongSo = 0;
				}
			}
		}
		if (tempString == "SP" || tempString == "sp" || tempString == "Sp")
		{
			int temp = pathList[0];
			for (int i = 0; i < temp + 1; i++)
			{
				pathList[i] = 0;
			}
			int batDau, ketThuc;
			fp >> batDau >> ketThuc;
			batDau--;
			ketThuc--;
			int result= ShortestPath_Find(DinhCount, batDau, ketThuc, maTranKe, maTranKe_size, d, f,pathList);
			fp2 << result << endl;
			if (result != -1)
			{
				for (int p = 1; p < pathList[0]; p++)
				{
					fp2 << pathList[p] << " " << pathList[p + 1] << endl;
				}
			}
		}
	}
}
void main()
{
	docFile(maTranKe, checkConnect, maTranKe_size, d, visited,pathList);
	cout << "Done!\n";
	system("pause");
}