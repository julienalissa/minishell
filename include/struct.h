/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:36:48 by ludebarn          #+#    #+#             */
/*   Updated: 2025/12/29 11:45:51 by ludebarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_env
{
	char	*key;
	char	*val;
	t_env	*next;
}			t_env;

typedef struct s_data
{
	t_env	env;
}			t_data;

