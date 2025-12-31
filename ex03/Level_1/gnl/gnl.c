#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char	*gnl(int fd)
{
	int i = 0;
	char current;
	int rd;
	char *line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
		
	rd = read(fd, &current, BUFFER_SIZE - BUFFER_SIZE + 1);
	line = malloc(600);
	while (rd > 0)
	{
		line[i++] = current;
		if (current == '\n')
			break;
		rd = read(fd, &current, 1);
	}
	line[i] = '\0';
	if (rd == -1 || i == 0 || line[i - 1] && rd == 0)
		return(free(line), NULL);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		line = gnl(fd);
		while (line != NULL)
		{
			printf("%s", line);
			free(line);
			line = gnl(fd);
		}
		close(fd);
	}
	return (0);
}
