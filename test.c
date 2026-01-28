#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	pid_t child1;
	pid_t child2;
	pid_t ret;
	int	status;
	int	returnstatus;
	char **cmd = malloc(sizeof(char *) * 3);
	cmd[0] = strdup("sleep");
	cmd[1] = strdup("bonjour");
	cmd[2] = NULL;

	child1 = fork();
	if (child1 == 0)
		execve("/bin/sleep", cmd, env);
	child2 = fork();
	if (child2 == 0)
		execve("/bin/sleep", cmd, env);
	while ((ret = waitpid(-1, &status, 0)) > 0)
	{
		if (WIFEXITED(status))
		{
			returnstatus = WEXITSTATUS(status);
			printf("L'enfant : [%d] à fini avec le code [%d]\n", ret, returnstatus);
		}
	}
}
