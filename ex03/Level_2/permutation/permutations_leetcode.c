#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	swap(int *c1, int *c2)
{
	int	temp;

	temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

int factorial(int n)
{
    int result = 1;
    int i = 1;
    while (i <= n)
    {
        result *= i;
        i++;
    }
    return (result);
}


void perm(int *nums, int start, int end, int **perms, int numsSize, int *i, int **returnColumnSizes)
{
    int current = start;
    int j;

    if (start == end)
    {
        perms[*i] = malloc(sizeof(int) * numsSize);
        (*returnColumnSizes)[*i] = numsSize;
        j = 0;
        while (j < numsSize)
        {
            perms[*i][j] = nums[j];
            j++;
        }
        (*i)++;
        return;
    }
    while (current <= end)
    {
        swap(nums + start, nums + current);
        perm(nums, start + 1, end, perms, numsSize, i, returnColumnSizes);
        swap(nums + start, nums + current);
        current++;
    }
}

int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    int start = 0;
    int **permutations;
    int end = numsSize - 1;
    int index = 0;
    int howmany = factorial(numsSize);
    int i = 0;

    *returnSize = factorial(numsSize);
    permutations = malloc(sizeof(int *) * *returnSize);
    *returnColumnSizes = (int*)malloc(*returnSize * sizeof(int));

    perm(nums, start, end, permutations, numsSize, &index, returnColumnSizes);
    return permutations;
}

int	main(void)
{
	int nums[] = {1, 2, 3};
	int numsSize = sizeof(nums) / sizeof(nums[0]);
	int returnSize = 0;
	int *returnColumnSizes[] = {0};

	int **perms = permute(nums, numsSize, &returnSize, returnColumnSizes);
	int i = 0;
	int j;
 

	while (i < returnSize)
	{
		j = 0;
		while (j < numsSize)
		{
			printf("%i\t", perms[i][j]);
            
			j++;
		}
		printf("\n");
		i++;
	}
}




               
