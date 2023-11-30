#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define m 3
#define n 3

int m1[m][n] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int m2[m][n] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

int add[m][n];
int sub[m][n];
int mul[m][n];

#define nth 5

void display(int mtx[m][n])
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d\t", mtx[i][j]);
		}
		printf("\n");
	}
}

void *addMtx(void *ind)
{
	long x = (long)ind;
	// printf("add %ld ", x);
	for (int i = x; i < (x + 1); i++)
	{
		for (int j = 0; j < n; j++)
		{
			add[i][j] = m1[i][j] + m2[i][j];
			printf("\naddition: Thread %ld change-add[%d][%d]=%d", x, i, j, add[i][j]);
		}
	}
	return NULL;
}

void *subMtx(void *ind)
{
	long x = (long)ind;
	// printf("sub %ld ", x);
	for (int i = x; i < (x + 1); i++)
	{
		for (int j = 0; j < n; j++)
		{
			sub[i][j] = m1[i][j] - m2[i][j];
			printf("\nSubtraction: Thread %ld change-sub[%d][%d]=%d", x, i, j, sub[i][j]);
		}
	}
	return NULL;
}

void *mulMtx(void *ind)
{
	long x = (long)ind;
	// printf("mul %ld ", x);
	for (int i = x; i < (x + 1); i++)
	{
		for (int j = 0; j < n; j++)
		{
			mul[i][j] = 0;
			for (int k = 0; k < n; k++)
			{
				mul[i][j] += m1[i][k] * m2[k][j];
				printf("\nMultiplication: Thread %ld change-mul[%d][%d]=%d", x, i, j, mul[i][j]);
			}
		}
	}
	return NULL;
}

int main()
{
	pthread_t th[nth];
	pthread_t threads[nth];
	pthread_t mth[nth];
	long id[nth];

	printf("\n Matrix 1:\n");
	display(m1);
	printf("\n Matrix 2:\n");
	display(m2);

	for (long i = 0; i < nth; i++)
	{
		pthread_create(&th[i], NULL, &addMtx, (void *)i);
		pthread_create(&threads[i], NULL, &subMtx, (void *)i);
		pthread_create(&mth[i], NULL, &mulMtx, (void *)i);
	}

	for (int i = 0; i < nth; i++)
	{
		pthread_join(th[i], NULL);
		pthread_join(threads[i], NULL);
		pthread_join(mth[i], NULL);
	}

	printf("\n\n Addition:\n");
	display(add);

	printf("\n Subtraction:\n");
	display(sub);

	printf("\n Multiplication:\n");
	display(mul);

	return 0;
}
