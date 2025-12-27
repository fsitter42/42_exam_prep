#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define _GNU_SOURCE
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

void f_filter(char *text, char *to_filter)
{
	int i = 0;
	int to_filter_len = strlen(to_filter);
	int j;

	while (text[i])
	{
		j = 0;
		while (to_filter[j] && text[i + j] == to_filter[j])
		{
			j++;
		}
		if (j == to_filter_len)
		{
			while (j > 0)
			{
				write(1, "*", 1);
				j--;
			}
			i += to_filter_len;
		}
		else
		{
			write(1, &text[i], 1);
			i++;
		}
	}
	
}


int main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return 1;

	char temp[BUFFER_SIZE];
	char *result = NULL;
	char *buffer;
	int i_read = 0;
	ssize_t bytes;

	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(result, i_read + bytes + 1);
		if (!buffer)
		{
			free(result);
			perror("malloc");
			return 1;
		}
		result = buffer;
		memmove(result + i_read, temp, bytes);
		i_read += bytes;
		result[i_read] = '\0';
	}
	if (bytes < 0)
	{
		perror("read");
		free(result);
		return 1;
	}
	if (!result)
		return 0;
	f_filter(result, av[1]);
	return (0);
}
