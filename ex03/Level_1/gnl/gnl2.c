#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFERSIZE
#define BUFFERSIZE 42
#endif

char *gnl(int fd)
{
	char *line = malloc(10000);
	char current;
	int i = 0;
	ssize_t lesen;
	
	while ((lesen = read(fd, &current, BUFFERSIZE - BUFFERSIZE + 1)) > 0)
	{
		line[i] = current;
		i++;
		if (current == '\n')			
			break;
	}
	line[i] = '\0';
	if (lesen == -1 || i == 0)
		return (free(line), NULL);
	i = 0;
	while (line[i])
		i++;
	char *realline = malloc(i + 1);
	i = 0;
	while (line[i])
	{
		realline[i] = line[i];
		i++;
	}
	i--;
	realline[i] = '\0';
	free(line);
	line = NULL;
	return (realline);
}

int main(void)
{
	int fd = open("subj.txt", O_RDONLY);
	int i = 0;
	char *line;
/*	line = gnl(fd);
	printf("%s\n", line);
		free(line);*/
	
	while ((line = gnl(fd)) != 0)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
