#include "../../include/minishell.h"

static void		exec_cmd(t_ast *node, t_data *data, int fd_in, int fd_out);
static int		command_count(t_ast *node);

void	setup_exec(t_ast *node, t_data *data)
{
	int total_cmds;

	if (!node)
		return;
	total_cmds = command_count(node);
	data->exec->pids = malloc(sizeof(pid_t) * total_cmds);
	if (!data->exec->pids)
		return ;
	data->exec->nb_cmds = 0;
	exec_ast(node, data, STDIN_FILENO, STDOUT_FILENO);
	wait_all_process(data);
	free(data->exec->pids);
	free_node(node);
	lstclear_token(&data->token);
	data->token = NULL;
	node = NULL;
}

void	exec_ast(t_ast *node, t_data *data, int fd_in, int fd_out)
{
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
			data->last_exit_code = execut_builtin(node, data);
		}
		else
		{
			data->exec->pids[data->exec->nb_cmds] = fork();
			if ((data->exec->pids[data->exec->nb_cmds]) == 0)
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
	{
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}
	execve (path, node->args, data->envp);
	perror(node->args[0]);
	free(path);
	ft_split_clear(node->args);
	if (node->redir)
		free(node->redir->file);
	if (errno == EACCES)
		exit (126);
	if (errno == ENOENT)
		exit (127);
	exit (1);
}

static int	command_count(t_ast *node)
{
	if (!node)
		return (0);
	if (node->op_type == NODE_CMD)
		return (1);
	return (command_count(node->left) + command_count(node->right));
}
