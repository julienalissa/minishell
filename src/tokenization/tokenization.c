#include "../../include/minishell.h"

void	skip_spaces(char *line, char ws, t_data *data);
char	*setup_value(char *line, char ws, t_data *data);
char	*define_states(char *line, t_data *data);

void	creat_token(char *line, t_data *data)
{
	char	*tmp;
	t_token *token_tmp;

	data->i = 0;
	while (line[data->i])
	{
		skip_spaces(line, ' ', data);
		if (line)
		{
			tmp = define_states(line, data);
			token_tmp = lstnew_token(tmp, data);
			if(!token_tmp)
			{
				free(tmp);
				lstclear_token(&data);
			}
			lstadd_back_token(&data->token, token_tmp);
 			free(tmp);
		}
		data->flag_states = NORMAL;
		data->i++;
	}
}

char	*define_states(char *line, t_data *data)
{
	char *tmp;

	tmp = NULL;
	if (line[data->i] == '"')
	{
		data->flag_states = DQUOTES;
		data->i++;
		tmp = setup_value(line, '"', data);
	}
	else if (line[data->i] == '\'')
	{
		data->flag_states = QUOTES;
		data->i++;
		tmp = setup_value(line, '\'', data);
	}
	else
		tmp = setup_value(line, ' ', data);
	return(tmp);
}

char	*setup_value(char *line, char ws, t_data *data)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[data->i + i] && line[data->i + i] != ws)
		i++;
	if (data->flag_states == QUOTES && line[data->i + i] == '\0')
		ft_error("Error : Unclosed quote"); // checker si on doit free
	else if (data->flag_states == DQUOTES && line[data->i + i] == '\0')
		ft_error("Error : Unclosed double quote");
	tmp = ft_substr(line, data->i, i);
	if (!tmp)
		return (NULL);
	data->i += ft_strlen(tmp);
	return (tmp);
}

void	skip_spaces(char *line, char ws, t_data *data)
{
	while (line[data->i] && line[data->i] == ws)
		data->i++;
}
