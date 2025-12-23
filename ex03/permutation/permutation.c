#include <stdio.h>
#include <string.h>

void	swap(char *c1, char *c2)
{
	char	temp;

	temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

void	sort(char *str)
{
	int		i;
	int		j;
	int		min;
	char	temp;
	int		length;

	i = 0;
	length = strlen(str);
	while (i < length - 2)
	{
		j = i + 1;
		min = i;
		while (j < length - 1)
		{
			if (str[j] < str[min])
				min = j;
			j++;
		}
		if (min != i)
		{
			temp = str[i];
			str[i] = str[min];
			str[min] = temp;
		}
		i++;
	}
}

void	perm(char *s, int start, int end)
{
	int	current;

	if (start == end)
		printf("%s\n", s);
	else
	{
		current = start;
		while (current <= end)
		{
			swap((s + start), (s + current));
			perm(s, start + 1, end);
			swap((s + start), (s + current));
			current++;
		}
	}
}

int	main(void)
{
	char str[42] = "askeijhg";
	sort(str);
	// printf("%s\n", str);
	perm(str, 0, strlen(str) - 1);
}