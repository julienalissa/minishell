#include "../../include/minishell.h"

static int	open_redir_out(char *file);
static int	open_redir_in(char *file);
static char	*get_file_redir_in(t_redir *redir);
static char	*get_file_redir_out(t_redir *redir);

void	define_redir(t_ast *node, int fd_in, int fd_out)
{
	int		final_in;
	int		final_out;
	char	*file_in;
	char	*file_out;

	if (node->redir && node->redir->redir_type == NODE_REDIR_IN)
	{
		file_in = get_file_redir_in(node->redir);
		final_in = open_redir_in(file_in);
	}
	else
		final_in = fd_in;
	if (node->redir && node->redir->redir_type == NODE_REDIR_OUT)
	{
		file_out = get_file_redir_out(node->redir);
		dprintf(2, "file_out = [%s]\n", file_out);
		final_out = open_redir_out(file_out);
	}
	else
		final_out = fd_out;
	dup_and_close(0, final_in);
	dup_and_close(1, final_out);
}

static int	open_redir_in(char *file)
{
	int	fd_in;

	fd_in = open(file, O_RDONLY);
	if (fd_in < 0)
	{
		perror("error: redir_in");
		exit(EXIT_FAILURE);
	}
	return (fd_in);
}

static int	open_redir_out(char *file)
{
	int	fd_out;

	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror("Error: redir_out");
		exit(EXIT_FAILURE);
	}
	return (fd_out);
}

static char	*get_file_redir_in(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;

	while (temp->next != NULL && temp->redir_type == NODE_REDIR_IN)
		temp = temp->next;
	return (temp->file);
}

static char	*get_file_redir_out(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;

	while (temp->next != NULL && temp->redir_type == NODE_REDIR_OUT)
	{
		temp = temp->next;
		dprintf(2, "%s\n", temp->file);
	}
	return (temp->file);
}
