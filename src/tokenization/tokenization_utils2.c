#include "../../include/minishell.h"

char	*remove_quote(char *line, t_data *data, char quote)
{
	int		i;
	int		start;
	char	*res;

	data->i++;
	start = data->i;
	i = 0;
	while (line[data->i + i] && line[data->i + i] != quote)
		i++;
	if (!line[data->i + i])
	{
		lstclear_token(&data->token);
		ft_printf("cheffff ferme les quotes");
		exit(1);
	}
	res = ft_substr(line, start, i);
	if (!res)
		return (NULL);
	data->i = data->i + i + 1;
	return (res);
}

void	make_quotes(char *line, t_data *data)
{
	t_token		*new;
	char		*res;

	if (line[data->i] == '\'')
	{
		res = remove_quote(line, data, '\'');
		new = lstnew_token(res, QUOTES);
		new->token_type = TOKEN_WORD;
	}
	else
	{
		res = remove_quote(line, data, '"');
		new = lstnew_token(res, DQUOTES);
		new->token_type = TOKEN_WORD;
	}
	lstadd_back_token(&data->token, new);
}

