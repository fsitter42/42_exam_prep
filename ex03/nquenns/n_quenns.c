#include <stdio.h>
#include <stdlib.h>

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

int	main(int ac, char *av)
{
	int n = 4;
	char **field = create_field(n);

	int i = 0;
	while (i < n)
	{
		printf("%s\n", field[i]);
		free(field[i]);
		i++;
	}
	free(field);
}