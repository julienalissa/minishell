/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:01:31 by ludebarn          #+#    #+#             */
/*   Updated: 2026/01/12 10:56:55 by lucasdebarn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_ast	*ast;
	char	*line;

	(void)argc;
	(void)argv;
	set_data(&data, env);
	creat_env(&data);
	signals();
	while (1)
	{
		line = readline("minishell > ");
		if (g_signal_received)
		{
			g_signal_received = 0;
			free(line);
			continue ;
		}
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (line && *line)
		{
			creat_token(line, &data);
			ast = build_ast(data.token, &data);
			if (ast)
				setup_exec(ast, &data);
			else
			{
				lstclear_token(&data.token);
				data.token = NULL;
			}
		}
		add_history(line);
		free(line);
	}
	lstclear_env(&data);
	return (data.last_exit_code);
}
