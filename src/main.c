/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:01:31 by ludebarn          #+#    #+#             */
/*   Updated: 2026/03/16 18:13:49 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_prog(t_data *data, t_ast *ast, char *line)
{
	if (g_signal_exit != 0)
	{
		data->last_exit_code = g_signal_exit;
		g_signal_exit = 0;
	}
	if (!line)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (line && *line)
	{
		creat_token(line, data);
		ast = build_ast(data->token, data);
		data->save_ast = ast;
		lstclear_token(&data->token);
		data->token = NULL;
		if (ast)
			setup_exec(ast, data);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_ast	*ast;
	char	*line;

	(void)argv;
	if (argc > 1)
		return (ft_putendl_fd("Usage: ./minishell", STDERR_FILENO), 0);
	set_data(&data, env);
	ft_bzero(&ast, sizeof(t_ast));
	signals();
	while (1)
	{
		line = readline("minishell > ");
		if (!exec_prog(&data, ast, line))
			break ;
		add_history(line);
		free(line);
		data.i = 0;
	}
	rl_clear_history();
	lstclear_env(&data);
	free(data.exec);
	return (data.last_exit_code);
}
