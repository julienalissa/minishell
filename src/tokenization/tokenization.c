/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   tokenization.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/27 13:22:51 by jualissa       #+#    #+#                */
/*   Updated: 2026/02/27 13:23:42 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	skip_spaces(char *line, t_data *data);
void	make_word(char *line, t_data *data);
char	*check_op(char *line, t_data *data);
void	make_op(char *line, t_data *data);

void	creat_token(char *line, t_data *data)
{
	data->i = 0;
	while (line[data->i])
	{
		skip_spaces(line, data);
		if (!line[data->i])
			break ;
		if (ft_strchr("<>()&|", line[data->i]))
			make_op(line, data);
		else if (line[data->i] == '\'' || line[data->i] == '"')
			make_quotes(line, data);
		else
			make_word(line, data);
	}
}

char	*remove_escape(char *str)
{
	char	*res;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i++;
			res[j++] = str[i++];
		}
		else
		{
			res[j++] = str[i++];
		}
	}
	res[j] = '\0';
	return (res);
}

void	make_word(char *line, t_data *data)
{
	char	*res;
	char	*cleaned;
	int		start;
	int		i;
	t_token	*new;

	start = data->i;
	i = 0;
	while (line[data->i + i])
	{
		if (line[data->i + i] == '\\' && line[data->i + i + 1])
		{
			i += 2;
		}
		else if (ft_strchr(" <>()&|\'\"", line[data->i + i]))
			break ;
		else
			i++;
	}
	if (i == 0)
		return;
	res = ft_substr(line, start, i);
	if (!res)
		return;
	data->i = data->i + i;
	cleaned = remove_escape(res);
	free(res);
	new = lstnew_token(cleaned, NORMAL);
	lstadd_back_token(&data->token, new);
	free(cleaned);
}

void	skip_spaces(char *line, t_data *data)
{
	while (line[data->i] && (line[data->i] == ' ' || (line[data->i] >= 9
				&& line[data->i] <= 13)))
		data->i++;
}

char	*check_op(char *line, t_data *data)
{
	char	*op;
	int		i;

	i = 1;
	if ((line[data->i] == '<' && line[data->i + 1] == '<')
		|| (line[data->i] == '>' && line[data->i + 1] == '>')
		|| (line[data->i] == '|' && line[data->i + 1] == '|')
		|| (line[data->i] == '&' && line[data->i + 1] == '&'))
		i = 2;
	op = ft_substr(line, data->i, i);
	data->i = data->i + i;
	return (op);
}

void	make_op(char *line, t_data *data)
{
	t_token	*new;
	char	*res;

	res = check_op(line, data);
	new = lstnew_token(res, NORMAL);
	lstadd_back_token(&data->token, new);
	free(res);
}
