#include "../../include/minishell.h"

int	cd(char **args,t_data *data)
{
	char	*path;
	int		ret;

	if (!args[1] || ft_strcmp(args[1],"~") == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_printf("home is unset\n");
			return (1);
		}
	}
	else
		path = args[1];
	ret = chdir(path);
	if (ret != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
