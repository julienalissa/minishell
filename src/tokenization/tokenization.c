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
			break;
		if (ft_strchr("<>()&|", line[data->i]))
			make_op(line, data);
		else if (line[data->i] == '\'' || line[data->i] == '"')
			make_quotes(line, data);
		else
			make_word(line, data);
	}
}

void	make_word(char *line, t_data *data)
{
	char	*res;
	int		start;
	int		i;
	t_token	*new;

	start = data->i;
	i = 0;
	while (line[data->i + i] && !ft_strchr( " <>()&|\'\"", line[data->i + i]))
		i++;
	if (i == 0)
		return;
	res = ft_substr(line, start, i);
	if (!res)
		return;
	data->i = data->i + i;
	new = lstnew_token(res, NORMAL);
	lstadd_back_token(&data->token, new);
	free(res);
}

void	skip_spaces(char *line, t_data *data)
{
	while (line[data->i] && (line[data->i] == ' ' || (line[data->i] >= 9 && line[data->i] <= 13)))
		data->i++;
}

char	*check_op(char *line, t_data *data)
{
	char	*op;
	int		i;

	i = 1;
	if ((line[data->i] == '<' && line[data->i + 1] == '<') ||
		(line[data->i] == '>' && line[data->i + 1] == '>') ||
		(line[data->i] == '|' && line[data->i + 1] == '|') ||
		(line[data->i] == '&' && line[data->i + 1] == '&'))
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

// void	creat_token(char *line, t_data *data)
// {
// 	char	*res;

// 	data->i = 0;
// 	while (line[data->i])
// 	{
// 		skip_spaces(line, data);
// 		if (line[data->i] == '\0')
// 			break;
// 		if (ft_strchr("<>()&|"), line[data->i])
// 		{
// 			res = check_op(line, data);
// 			data->flag_states = NORMAL;
// 		}
// 		else if (line[data->i] && line[data->i] == '\'' || line[data->i] == '\"')

// 		else
// 		{
// 			data->flag_states = NORMAL;
// 			res = setup_value(line, ' ', data);
// 		}
// 		new_node = lstnew_token(res, data);
// 		lstadd_back_token(&data->token, new_node);
// 		free(res);
// 	}
// }

// char	*check_quotes(char *line, t_data *data)
// {
// 	char	*res;

// 	quote = line[data->i];
// }

// char	*setup_value(cha r *line, char ws, t_data *data)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	while (line[data->i + i] && line[data->i + i] != ws)
// 		i++;
// 	if (data->flag_states == QUOTES && line[data->i + i] == '\0')
// 		ft_error("Error : Unclosed quote"); // checker si on doit free
// 	else if (data->flag_states == DQUOTES && line[data->i + i] == '\0')
// 		ft_error("Error : Unclosed double quote");
// 	tmp = ft_substr(line, data->i, i);
// 	if (!tmp)
// 		return (NULL);
// 	data->i += ft_strlen(tmp);
// 	return (tmp);
// }



// void	put_token(t_token *)
