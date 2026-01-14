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
	t_data data;

	(void)argc,
	(void)argv;
	char	*line;

	set_data(&data, env);
	creat_env(&data);
	line = readline("minishell > ");
	creat_token(line, &data);
	// while(1)
	// {
	// 	data.env = data.env->next;
	// 	printf("Key = %s\nValue = %s\n", data.env->key, data.env->val);
	// 	if (data.env->next == NULL)
	// 		break;
	// }
	return (0);
}
