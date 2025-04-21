#include "../../includes/shellinho.h"

void ft_or_wrapper(t_info *info, t_tree *node)
{
	pid_t	pid;
	int		status;

	if (!info || !node)
		return ;
    if (node->type == OR)
    {
        if (node->left && node->right)
        {
            ft_or_wrapper(info, node->left);
            if (exit_status != 0)   
                ft_or_wrapper(info, node->right);
        }
        else
        {
            ft_putstr_fd("Shellinho: syntax error\n", 2);
            exit_status = 2;
            free_tree(node);
        }
    }
    else
    {
        if (check_builtins(info) == 0)
            return ;
        pid = fork();
        if (pid == -1)
            return (ft_putstr_fd("Fork error", 2));
        if (pid == 0)
            exec_command(info, node);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) // verifica se terminou normalmente
            exit_status = WEXITSTATUS(status);
    }
}

void ft_or(t_info *info)
{
    if (!info)
        return ;
    ft_or_wrapper(info, info->cmd_tree);
}