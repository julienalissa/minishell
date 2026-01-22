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

	(void)argc,
	(void)argv;
	set_data(&data, env);
	creat_env(&data);
	while(1)
	{
		line = readline("minishell > ");
		if (!line)
			break;
		if (line && *line)
		{
			creat_token(line, &data);
			ast = build_ast(data.token, &data);
			lstclear_token(&data.token);
		}
		free(line);
	}
	lstclear_env(&data);
	return (0);
}
