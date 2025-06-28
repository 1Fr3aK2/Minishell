


#include "../../../includes/minishell.h"

static void	child_exec(t_info *info, t_tree *node, int in, int out)
{
	printf("[child_exec] PID %d | in_fd=%d, out_fd=%d\n", getpid(), in, out);
	dup_pipe_fds(in, out);
	if (check_redirections_node(node, info) == 0)
		ft_exit2(info);
	handle_heredoc(node);
	if (node->type == CMD)
	{
		if (is_builtin(info->builtins->builtins, node->args[0]) == 0)
			exec_builtins(node->args, info, node);
		else
			exec_command(info, node);
	}
	else
		exec_comand_op(info, node);
	ft_exit2(info);
}

static pid_t	handle_pipe_fork(t_info *info, t_tree *node, int in, int *fd)
{
	pid_t pid;

	printf("fd criado -> %d\n", fd[0]);
	printf("fd criado -> %d\n", fd[1]);

	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		printf("fechou o fd -> %d (filho)\n", fd[0]);
		close(fd[0]);
		child_exec(info, node->left, in, fd[1]);
	}
	printf("fechou o fd -> %d (parent)\n", fd[1]);
	close(fd[1]);

	return (pid);
}

static pid_t	create_pipe(t_info *info, t_tree *node, int in, int *out)
{
	int		fd[2];
	pid_t	pid;
	int		has_heredoc;

	has_heredoc = node->right && node->right->io
		&& node->right->io->heredoc_fd != -1;
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Pipe error\n", 2);
		return (-1);
	}
	printf("[create_pipe] Pipe created: fd[0]=%d (read), fd[1]=%d (write)\n", fd[0], fd[1]);
	pid = handle_pipe_fork(info, node, in, fd);
	if (pid == -1)
		return (-1);
	
	// CORREÇÃO: Fechar o fd de input anterior APENAS após o fork
	if (in != -1)
	{
		printf("fechou o fd -> %d (parent - input anterior)\n", in);
		close(in);
	}
	
	if (has_heredoc)
	{
		printf("[create_pipe] Heredoc detected, closing fd[0] %d, setting *out = -1\n", fd[0]);
		close(fd[0]);
		*out = -1;
	}
	else
	{
		printf("[create_pipe] Setting *out = fd[0] %d for next command input\n", fd[0]);
		*out = fd[0];
	}
	return (pid);
}

void	ft_pipe(t_info *info, t_tree *node)
{
	t_tree	*curr;
	pid_t	pid;
	int		in;

	in = -1;
	curr = node;
	pid = -1;
	while (curr && curr->type == PIPE)
	{
		pid = create_pipe(info, curr, in, &in);
		if (pid == -1)
			return ;
		printf("[ft_pipe] Pipe criado, novo in fd: %d\n", in);
		curr = curr->right;
	}
	if (curr)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("escreve para o fd -> %d (último comando)\n", in);
			child_exec(info, curr, in, -1);
		}
	}
	
	// CORREÇÃO: Esperar todos os filhos terminarem ANTES de fechar o último fd
	wait_all(pid, info);
	
	if (in != -1)
	{
		printf("fechou o fd -> %d (parent - último in após wait)\n", in);
		close(in);
	}
	close_heredoc_fds(info->cmd_tree);
}

void	ft_pipe_wrapper(t_info *info)
{
	if (!info || !info->cmd_tree)
		return ;
	prepare_heredocs(info->cmd_tree, info);
	if (info->exit_status == 130)
		return ;
	ft_pipe(info, info->cmd_tree);
	close_heredoc_fds(info->cmd_tree);
}