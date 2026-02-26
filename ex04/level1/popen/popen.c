#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_popen(const char *file, char *const argv[], char type);

int	ft_popen(const char *file, char *const argv[], char type)
{
	int		fds[2];
	pid_t	pid;

	if (!file || !*file || !argv || !argv[0] || (type != 'w' && type != 'r'))
		return (-1);
	if (pipe(fds) == -1)
		return (-1);
	if ((pid = fork()) == -1)
		return (-1);
	if (type == 'r')
	{
		if (pid == 0)
		{
			//close the read
			close(fds[0]);
			//stecker von write in loch von stdout
			dup2(fds[1], 1);
			//close den write
			close(fds[1]);
			//execvp von file
			//if it fails return -1
			if(execvp(file, argv) == -1)
				exit(127);
		}
		else
		{
			//close write
			close(fds[1]);
			//read read
			return(fds[0]);
			//oder return read
		}
	}
	if (type == 'w')
	{
		if (pid == 0)
		{
			//close write
			close(fds[1]);
			// stecker von read and stdin
			dup2(fds[0], 0);
			//close read
			close(fds[0]);
			execvp(file, argv);
			exit (127);
			//execvp von file
			//if it fails return -1
		}
		else
		{
			//close read
			close(fds[0]);
			//return write
			return(fds[1]);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	int		ret;
	char	*args[] = {"ls", NULL};

	(void)(ac);
	(void)(av);
	(void)envp;
	ret = execvp(args[0], args);
	printf("%i\n", ret);
	return (0);
}
