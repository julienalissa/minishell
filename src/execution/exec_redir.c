#include "../../include/minishell.h"

int	open_redir_out(char *file);
int	open_redir_in(char *file);

void	define_redir(t_ast *node, int fd_in, int fd_out)
{
	int	final_in;
	int	final_out;

	if (node->redir && node->redir->redir_type == NODE_REDIR_IN)
		final_in = open_redir_in(node->redir->file);
	else
		final_in = fd_in;
	if (node->redir && node->redir->redir_type == NODE_REDIR_OUT)
		final_out = open_redir_out(node->redir->file);
	else
		final_out = fd_out;
	dup_and_close(0, final_in);
	dup_and_close(1, final_out);
}

int	open_redir_in(char *file)
{
	int	fd_in;

	fd_in = open(file, O_RDONLY);
	if (fd_in < 0)
	{
		perror("error: redir_in");
		exit(EXIT_FAILURE); // a checker si c'est le comportement a faire ?
	}
	return (fd_in);
}

int	open_redir_out(char *file)
{
	int	fd_out;

	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror("Error: redir_out");
		exit(EXIT_FAILURE); // a checker si c'est le comportement a faire ?
	}
	return (fd_out);
}
