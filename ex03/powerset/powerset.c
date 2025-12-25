#include <stdio.h>
#include <stdlib.h>

void	powerset(int *array, int start, int end, int value);

int	main(int ac, char **av)
{
	int	i;
	int	value;
	int	*set;
	int	setsize;

	if (ac < 3)
		return (0);
	i = 2;
	setsize = ac - 2;
	value = atoi(av[1]);
	while (i < ac)
	{
		set[i - 2] = atoi(av[i]);
		i++;
	}
	i = 0;
	powerset(set, 0, setsize, value);
}

void	powerset(int *array, int start, int end, int value)
{
	if (start == end)
		return ;
	else if (array[start] == value)
		printf("%i\n", array[start]);
	int i = start + 1;
	while (i < end)
	{
		if (array[start] + array[i] == value)
			printf("%i %i\n", array[start], array[i]);
		i++;
	}
	powerset(array, start + 1, end, value);
}