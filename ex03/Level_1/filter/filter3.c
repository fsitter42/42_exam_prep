#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 42

void f_filter(char *text, char *filter)
{
	size_t lenoffilter = strlen(filter);
	int i = 0;
	int j;

	while (text[i])
	{
		j = 0;
		while (filter[j] && text[i + j] == filter[j])
			j++;
		if (j == lenoffilter)
		{
			while (j > 0)
			{
				write(1, "*", 1);
				j--;
			}
			i += lenoffilter;
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
	if (ac!= 2)
		return 1;

	char *text = malloc (10000);
	if (!text)
		return(perror("ERROR: malloc\n"), 1);
	ssize_t lesen;
	int i = 0;
	char current;

	while ((lesen = read(0, &current, BUFFERSIZE - BUFFERSIZE + 1)) > 0)
	{
		text[i] = current;
		i++;
	}
	if (lesen < 0)
		return(free(text), perror("ERROR: read\n"), 1);
	if (!text)
		return (0);
	f_filter(text, av[1]);
	return (0);
}