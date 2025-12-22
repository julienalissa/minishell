#include "minishell.h"
// creat_token()

int	main(void)
{
	char	*line;
	while (1)
	{
		line = readline("minishell : ");
		printf("%s", line);
		break;
	}
	return (0);
}

//gcc minishell.c -lreadline
