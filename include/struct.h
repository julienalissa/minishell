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

typedef enum e_token_type
{
	TOKEN_WORD, // 0
	TOKEN_PIPE,// 1
	TOKEN_REDIR_IN, // 2
	TOKEN_REDIR_OUT, // 3
	TOKEN_HEREDOC, // 4
	TOKEN_APPEND, //5
	TOKEN_AND, //6
	TOKEN_OR, //7
	TOKEN_PARENTHESIS_IN, //8
	TOKEN_PARENTHESIS_OUT //9
} t_token_type;

typedef struct s_token
{
	t_token_type token_type;
	char	*value;
	struct s_token *next;
}t_token;

// typedef struct s_env
// {
// 	char	*key;
// 	char	*val;
// 	t_env	*next;
// }			t_env;

typedef struct s_data
{
	int	i;
	int	argc;
	char **argv;
	char **env;
	t_token *token;
}	t_data;

