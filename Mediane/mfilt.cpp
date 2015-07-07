#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <cstring>
#include <ctime>

DWORD dwCounter;
HANDLE *aThread;
HANDLE** mtx;

int **A, **B;
int m, n;

void BubbleSort(int* a, int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] > a[j + 1])
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

DWORD WINAPI MFiltre(LPVOID arg)
{
    srand(time(0));
    int C[9];
    memset(C, 0, sizeof(C));
	int i = (int)arg / n;
    int j = (int)arg % m;
    
    int ind = 0;
    WaitForSingleObject(mtx[i][j], INFINITE);
    C[ind++] = A[i][j];
    ReleaseMutex(mtx[i][j]);

    if (i > 0)
    {
        if (j > 0)
        {
            WaitForSingleObject(mtx[i - 1][j - 1], INFINITE);
            C[ind++] = A[i - 1][j - 1];
            ReleaseMutex(mtx[i - 1][j - 1]);
        }

        WaitForSingleObject(mtx[i - 1][j], INFINITE);
        C[ind++] = A[i - 1][j];
        ReleaseMutex(mtx[i - 1][j]);

        if (j < (n - 1))
        {
            WaitForSingleObject(mtx[i - 1][j + 1], INFINITE);
            C[ind++] = A[i - 1][j + 1];
            ReleaseMutex(mtx[i - 1][j + 1]);
        }
    }

    if (i < (m - 1))
    {
        if (j > 0)
        {
            WaitForSingleObject(mtx[i + 1][j - 1], INFINITE);
            C[ind++] = A[i + 1][j - 1];
            ReleaseMutex(mtx[i + 1][j - 1]);
        }

        WaitForSingleObject(mtx[i + 1][j], INFINITE);
        C[ind++] = A[i + 1][j];
        ReleaseMutex(mtx[i + 1][j]);

        if (j < (n - 1))
        {
            WaitForSingleObject(mtx[i + 1][j + 1], INFINITE);
            C[ind++] = A[i + 1][j + 1];
            ReleaseMutex(mtx[i + 1][j + 1]);
        }
    }

    if (j > 0)
    {
        WaitForSingleObject(mtx[i][j - 1], INFINITE);
        C[ind++] = A[i][j - 1];
        ReleaseMutex(mtx[i][j - 1]);
    }
    if (j < (n - 1))
    {
        WaitForSingleObject(mtx[i][j + 1], INFINITE);
        C[ind++] = A[i][j + 1];
        ReleaseMutex(mtx[i][j + 1]);
    }
 
    BubbleSort(C, ind);
    B[i][j] = C[ind / 2];
    return 0;

	free(C);

}
int rAB(int a, int b)
{
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[])
{
    DWORD ThreadID;

	while(true)
	{
		printf("Strings\n");
		scanf_s("%d", &m);
	

		printf("Columns\n");
		scanf_s("%d", &n);

		if(m == 0 || n == 0)
		{
			printf("Enter correct value(s) please\n");
			continue;
			//return 0;
		}
	


		dwCounter = n * m;
		aThread = (HANDLE *)malloc(sizeof(HANDLE)* dwCounter);

		//Sourse matrix
		A = (int**)malloc(sizeof(int*)* m);
		mtx = (HANDLE**)malloc(sizeof(HANDLE*)* m);
		B = (int**)malloc(sizeof(int*)* m);

		for (int i = 0; i < m; ++i)
		{
			A[i] = (int*)malloc(sizeof(int)* n);
			mtx[i] = (HANDLE*)malloc(sizeof(HANDLE)* n);
			B[i] = (int*)malloc(sizeof(int)* n);
		}

		//Destination matrix

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				A[i][j] = B[i][j] = rAB(-15, 20);
				mtx[i][j] = CreateMutex(NULL, FALSE, NULL);
			}
		}

		for (int i = 0; i < m * n; i++)
		{
			aThread[i] = CreateThread(NULL, 0, MFiltre, (LPVOID)i, 0, &ThreadID);
		}

		for (int i = 0; i < m * n; i++)
		{
			WaitForSingleObject(aThread[i], INFINITE);
			CloseHandle(aThread[i]);
		}

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				printf("%4d", A[i][j]);
			}
			printf("\n\n");
		}
		printf("\n\n");
		printf("\n\n");
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				printf("%4d", B[i][j]);
			}
			printf("\n\n");
		}

		free(B);
		free(A);
		continue;

		return 0;
	}
} 