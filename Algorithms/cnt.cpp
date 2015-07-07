#include <cstdio>

typedef int TKey;
typedef unsigned long long TVal;

struct TEl
{
	TKey key;
	TVal value;
};

void CountSort(TEl** a, int n);
void SwapVectors(TEl** a, TEl** b);

int main()
{
	TEl pb;
	int size = 0;
	int cap = 1;
	TEl* v = new TEl[cap];
	
	while (scanf("%d\t%llu", &pb.key, &pb.value) == 2)
	{
		if (size == cap)
		{
			cap *= 2;

			TEl* vTmp = new TEl[cap];

			for (int i = 0; i < size; ++i)
			{
				vTmp[i] = v[i];
			}

			delete[] v;

			v = vTmp;
		}

		v[size] = pb;
		size++;
	}

	CountSort(&v, size);
	
	for (int i = 0; i < size; i++)
	{
		printf("%06d\t%llu\n", v[i].key, v[i].value);
	}
	
	delete[] v;

	return 0;
}

void CountSort(TEl** a, int n)
{
	if (n < 2)
	{
		return;
	}

	TKey max = (*a)[0].key;

	for (int i = 0; i < n; i++)
	{
		if ((*a)[i].key > max)
		{
			max = (*a)[i].key;
		}
	}

	TEl* a2 = new TEl[n];
	int* c = new int[max + 1];

	for (int i = 0; i <= max; i++)
	{
		c[i] = 0;
	}

	for (int i = 0; i < n; i++)
	{
		c[(*a)[i].key]++;
	}

	for (int i = 1; i <= max; i++)
	{
		c[i] += c[i - 1];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		a2[c[(*a)[i].key] - 1] = (*a)[i];
		--c[(*a)[i].key];
	}

	SwapVectors(a, &a2);

	delete[] a2;
	delete[] c;
}

void SwapVectors(TEl** a, TEl** b)
{
	TEl* c = *a;
	*a = *b;
	*b = c;
}