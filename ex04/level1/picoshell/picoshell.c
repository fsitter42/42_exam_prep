#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//need?
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int    picoshell(char **cmds[]);

int    picoshell(char **cmds[])
{
    pid_t pid; // für fork
	int fd[2]; // für pipe
	int last_fd = -600; // als markierung für start
	int i = 0; // um durch cmd zu iterieren
	
	while (cmds[i])
	{
		if (cmds[i + 1]) // wenn es noch einen cmd gibt pipe öffnen
		{
			if (pipe(fd) == -1)
				return (1);
		}
		pid = fork();
		if (pid == -1) // wenn fork failed
		{
			if (cmds[i + 1]) // wenn wir eine pipe gemacht haben
			{
				close(fd[1]);
				close(fd[0]);
			}
			return (1);
		}
		else if (pid == 0) // im kind
		{
			if (last_fd != -600) // wenn nicht der erste cmd, read ende auf stdin stecken 0 zu 0
			{
				if (dup2(last_fd, 0) == -1)
					exit (1);
				close(last_fd);
			}
			if (cmds[i + 1]) // wenn nicht der letzt cmd, write ende auf stdout 1 zu 1
			{
				close(fd[0]);
				if (dup2(fd[1], 1) == -1)
					exit (1);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit (1);
		}
		else // im the parent
		{
			if (last_fd != -600) // wenn nicht der erste command den von davor schließen
				close(last_fd);
			if (cmds[i + 1]) // wenn es noch einen cmd gibt schreiben schließen und last auf lesen setzten damit kind aus last lesen kann
			{
				close(fd[1]);
				last_fd = fd[0];
			}
		}
		i++;
	}
	while (wait(NULL) > 0)
	{
		;
	}
	return (0);
}
