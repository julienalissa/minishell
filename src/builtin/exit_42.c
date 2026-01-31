#include "../../include/minishell.h"

int exit_42(char **args)
{
	int status;

	status = 0;
	ft_printf("exit\n");
	if (args[1])
		status = ft_atoi(args[1]);
	exit(status);
}
