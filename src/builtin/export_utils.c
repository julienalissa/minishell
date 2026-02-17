#include "../../include/minishell.h"

int	is_valid(char *s)
{
	int	i;

	i = 1;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
