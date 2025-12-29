/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:01:31 by ludebarn          #+#    #+#             */
/*   Updated: 2025/12/29 11:46:46 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void define_token(t_token *node)
{
	if (ft_strncmp(node->value, "|", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_PIPE;
	else if (ft_strncmp(node->value, "<", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_REDIR_IN;
	else if (ft_strncmp(node->value, ">", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_REDIR_OUT;
	else if (ft_strncmp(node->value, "<<", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_HEREDOC;
	else if (ft_strncmp(node->value, ">>", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_APPEND;
	else if (ft_strncmp(node->value, "&&", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_AND;
	else if (ft_strncmp(node->value, "||", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_OR;
	else if (ft_strncmp(node->value, "(", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_PARENTHESIS_IN;
	else if (ft_strncmp(node->value, ")", ft_strlen(node->value)) == 0)
		node->token_type = TOKEN_PARENTHESIS_OUT;
	else
		node->token_type = TOKEN_WORD;
}

void	skip_spaces(char *line, char ws, t_data *data)
{
	while (line[data->i] && line[data->i] == ws)
		data->i++;
}

char	*setup_value(char *line, char ws, t_data *data)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[data->i + i] && line[data->i + i] != ws)
		i++;
	tmp = ft_substr(line, data->i, i);
	if (!tmp)
		return (NULL);
	data->i += ft_strlen(tmp);
	return (tmp);
}

char	*creat_nodes(char *line, t_data *data)
{
	char	*tmp;
	t_token *token_tmp;

	data->i = 0;
	while (line[data->i])
	{
		skip_spaces(line, ' ', data);
		if (line)
		{
			tmp = setup_value(line, ' ', data);
			token_tmp = ft_lstnew_token(tmp);
			ft_lstadd_back_token(&data->token, token_tmp); // free token_tmp
			printf("%d",data->token->token_type);
 			free(tmp);
			ft_lstclear_token(&token_tmp);
		}
		data->i++;
	}
	return (NULL);
}

void	set_data(t_data *data, int argc, char **argv, char **env)
{
	ft_bzero(data, sizeof(data));
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	data->token = malloc(sizeof(t_token));
}

int	main(int argc, char **argv, char **env)
{
	t_data data;


	char	*line;

	set_data(&data, argc, argv, env);
	while (1)
	{
		line = readline("minishell : ");
		if (!creat_nodes(line, &data))
			break;
	}
	return (0);
}
