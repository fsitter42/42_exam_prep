#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int    picoshell(char **cmds[]);

int    picoshell(char **cmds[])
{
	pid_t pid;
	int fd[2];
	int lfd = -1;
	int i = 0;

	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(fd) == -1)
				return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			if (cmds[i + 1])
			{
				close(fd[0]);
				close(fd[1]);
			}
			return (1);
		}
		else if (pid == 0)
		{
			if (lfd != -1)
			{
				if (dup2(lfd, 0) == -1)
					exit (1);
				close(lfd);
			}
			if (cmds[i +1])
			{
				close(fd[0]);
				if (dup2(fd[1], 1) == -1)
					exit (1);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit (1);
		}
		else
		{
			if (lfd != -1)
				close(lfd);
			if (cmds[i + 1])
			{
				close(fd[1]);
				lfd = fd[0];
			}
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	return (0);	
}