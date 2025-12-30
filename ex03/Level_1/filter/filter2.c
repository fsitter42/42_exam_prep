#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

void ffffilter(char *input, char*filter)
{
	size_t i = 0;
	size_t j;
	while (input[i])
	{
		j = 0;
		while (filter[j] && input[i + j] == filter[j])
			j++;
		if (strlen(filter) == j)
		{
			while (j-- > 0)
				write(1, "x", 1);
			i += strlen(filter);
		}
		else
			write(1, &input[i++], 1);
	}
}

int main(int ac, char **av)
{
	if (ac != 2 || !av[1] || !*av[1])
	{
		write(2, "read description\n", 18);
		return (1);
	}
	char temp[BUFFER_SIZE];
	char *buffer;
	char *input = NULL;
	size_t where_am_i = 0;
	ssize_t bytes;


	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(input, where_am_i + bytes + 1);
		if (!buffer)
		{
			perror("buffer\n");
			free(input);
			return (1);
		}
		input = buffer;
		memmove(input+where_am_i, temp, bytes);
		where_am_i += bytes;
		input[where_am_i] = '\n';
	}
	if (bytes < 0)
	{
		perror("read\n");
		free(input);
		return (1);
	}
	if (!input)
		return (1);
	ffffilter(input, av[1]);
	return (0);
}