#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	**create_field(int n);
char	**free_field(char **field, int field_size);
void	n_queens(char **field, int start, int end);
int		safe();

int safe()
{
	return 1;
}

void	n_queens(char **field, int start, int end)
{
	if (start == end)
	{
		int i = 0;
		int j;
		int queen;
		while (i < end-1)
		{
			j = 0;
			queen = 0;
			while (j < end)
			{
				if (field[i][j] != 48)   
				{
					queen = j;
				}
				j++;
			}
			printf("%i ", queen);
			i++;
		}
		j = 0;
		queen = 0;
		while (j < end)
		{
			if (field[i][j] != 48)
			{
				queen = j;
			}
			j++;
		}
		printf("%i\n", queen);
	}
	else
	{
		int col = 0;
		while (col < end)
		{
			if (safe())
			{
				field[start][col] = 81;
				n_queens(field, start+1, end);
				field[start][col] = 48;
			}
			col++;
		}
	}
}


char	**create_field(int n)
{
	char	**field;
	int		i;
	int		j;

	field = (char **)calloc(n + 1, sizeof(char *));
	if (!field)
		return (NULL);
	field[n] = NULL;
	i = 0;
	while (i < n)
	{
		field[i] = (char *)calloc(n + 1, sizeof(char));
		j = 0;
		while (j < n)
		{
			field[i][j] = 48;
			j++;
		}
		field[i][j] = '\0';
		i++;
	}
	return (field);
}

char	**free_field(char **field, int field_size)
{
	int	i;

	i = 0;
	while (i < field_size)
	{
		free(field[i]);
		i++;
	}
	free(field);
	field = NULL;
	return (field);
}

int	main(int ac, char **av)
{
	int		n;
	char	**field;
	int		i;

	n = 4;
	field = create_field(n);

	// field[0][1] = 'Q';
	// field[1][3] = 'Q';
	// field[2][0] = 'Q';
	// field[3][2] = 'Q';


	// print
	i = 0;
	while (i < n)
		printf("%s\n", field[i++]);

	n_queens(field, 0, n);
	// free
	field = free_field(field, n);
}
