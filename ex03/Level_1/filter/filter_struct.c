#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

typedef struct s_filter
{
	char	temp[BUFFER_SIZE];
	char	*result;
	size_t	where_am_i;
	ssize_t	bytes;
	char	*to_filter;
	size_t	to_filter_len;
}			t_filter;

void	f_filter(t_filter *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->result[i])
	{
		j = 0;
		while (data->to_filter[j] && data->result[i + j] == data->to_filter[j])
			j++;
		if (j == data->to_filter_len)
		{
			while (j-- > 0)
				write(1, "*", 1);
			i += data->to_filter_len;
		}
		else
			write(1, &data->result[i++], 1);
	}
}

int	main(int ac, char **av)
{
	t_filter	data;
	char		*buffer;

	if (ac < 2 || !av[1] || !*av[1])
	{
		write(2, "Usage: ./a.out <string_to_filter>\n", 35);
		return (1);
	}
	data.result = NULL;
	data.where_am_i = 0;
	data.to_filter = av[1];
	data.to_filter_len = strlen(av[1]);
	while ((data.bytes = read(0, data.temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(data.result, data.where_am_i + data.bytes + 1);
		if (!buffer)
		{
			free(data.result);
			perror("malloc");
			return (1);
		}
		data.result = buffer;
		memmove(data.result + data.where_am_i, data.temp, data.bytes);
		data.where_am_i += data.bytes;
		data.result[data.where_am_i] = '\0';
	}
	if (data.bytes < 0)
	{
		free(data.result);
		perror("read");
		return (1);
	}
	if (!data.result)
		return (0);
	f_filter(&data);
	free(data.result);
	return (0);
}
