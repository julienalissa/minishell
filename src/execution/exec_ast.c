#include "../../include/minishell.h"

static void		exec_cmd(t_ast *node, t_data *data, int fd_in, int fd_out);
static int		command_count(t_ast *node);

void	setup_exec(t_ast *node, t_data *data)
{
	int total_cmds;

	total_cmds = command_count(node);
	data->exec->pids = malloc(sizeof(pid_t) * total_cmds);
	if (!data->exec->pids)
		return ;
	data->exec->nb_cmds = 0;
	exec_ast(node, data, STDIN_FILENO, STDOUT_FILENO);
	wait_all_process(data);
	free(data->exec->pids);
	lstclear_token(&data->token);
	data->token = NULL;
	node = NULL;
}

void	exec_ast(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	int i;

	i = data->exec->nb_cmds;
	if (!node)
		return ;
	if (node->op_type == NODE_PIPE)
		exec_pipe(node, data, fd_in, fd_out);
	else if (node->op_type == NODE_AND)
		exec_and(node, data, fd_in, fd_out);
	else if (node->op_type == NODE_OR)
		exec_or(node, data, fd_in, fd_out);
	else if (node->op_type == NODE_CMD)
	{
		if (is_builtin(node->args[0]))
		{
			define_redir(node, fd_in, fd_out);
			execut_builtin(node, data);
		}
		else
		{
			data->exec->pids[i] = fork();
			if ((data->exec->pids[i]) == 0)
				exec_cmd(node, data, fd_in, fd_out);
			data->exec->nb_cmds++;
		}
	}
}

static void	exec_cmd(t_ast *node, t_data *data, int fd_in, int fd_out)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	define_redir(node, fd_in, fd_out);
	if ((path = find_path(node, data)) == NULL)
		return(ft_error("Error: PATH NO FOUND\n"));
	if ((execve (path, node->args, data->envp)) < 0)
	{
		free(path);
		ft_split_clear(node->args);
		if (node->redir)
			free(node->redir->file);
		ft_error("Error: Execve failled");
	}
}

static int	command_count(t_ast *node)
{
	if (!node)
		return (0);
	if (node->op_type == NODE_CMD)
		return (1);
	return (command_count(node->left) + command_count(node->right));
}
