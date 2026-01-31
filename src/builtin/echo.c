#include "../../include/minishell.h"

int echo(char **args)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline == 1)
		write(1, "\n", 1);
	return (0);
}
