#include "../../include/minishell.h"

int	pwd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	return (0);
}
