#include <stdio.h>
#include <stdlib.h>

void powerset(int *s, int start, int end, int target, int count)
{
	if (start > end)
		return;
	if (count == target)
	{
		int i = 0;
		while (i < start)
		{
			if (s[i] != -600)
			{
				if (i < start - 1)
					printf("%i ", s[i]);
				else
					printf("%i", s[i]);
			}
			i++;
		}
		printf("\n");
		// if (s[i] != 0)
		// 	printf("%i\n", s[i]);
	}
	else if (count > target)
		return;
	else if (count < target)
	{
		int old_value = s[start];
		powerset(s, start + 1, end, target, count + s[start]);
		s[start] = -600;
		powerset(s, start + 1, end, target, count + 0);
		s[start] = old_value;
	}
}

int	main(int ac, char **av)
//int main(void)
{
	//int ac = 7;
	// char *av[] = {"name", "5", "1", "2", "3", "4", "5", NULL};
	if (ac < 3)
		return (-1);
	int target = atoi(av[1]);
	int setsize = ac - 2;
	int *set = malloc(sizeof(int) * setsize);
	int i = 2;

	while (av[i] != NULL)
	{
		set[i - 2] = atoi(av[i]);
		i++;
	}
	
	powerset(set, 0, setsize, target, 0);
}