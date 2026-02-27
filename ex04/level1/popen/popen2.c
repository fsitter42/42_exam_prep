#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_popen(const char *file, char *const argv[], char type);

int	ft_popen(const char *file, char *const argv[], char type)
{
	int		fd[2];
	pid_t	pid;

	if (!file || !*file || !argv || !argv[0])
		return (-1);
	if (type != 'r' && type != 'w')
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	if ((pid = fork()) == -1)
        return (-1);
    if (type == 'r')
    {
        if (pid == 0)
        {
            //close the read, plug the write to 1, close write, call system, exit on error
            close(fd[0]);
            dup2(fd[1], 1);
            close(fd[1]);
            execvp(file, argv);
            exit(127);
        }
        else
        {
            close(fd[1]);
            return (fd[0]);
        }
    }
    else if (type == 'w')
    {
        if (pid == 0)
        {
            //close the write, plug read to 0, close read, systemcall, exit on error
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            execvp(file, argv);
            exit(127);
        }
        else
        {
            close(fd[0]);
            return (fd[1]);
        }
    }
}
