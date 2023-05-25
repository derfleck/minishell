#include "../../inc/minishell.h"

static void	execute_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->cmd == NULL)
		return ;
	if (cmd->cmd && ft_strncmp("./", cmd->cmd, 2) != 0)
	{
		tmp = get_cmd_with_path(cmd, shell->paths);
		if (!tmp)
		{
			printf("%s: command not found\n", cmd->cmd);
			return ;
		}
		if (execve(tmp, cmd->arg, shell->envp) == -1)
			perror("execve");
	}
	else
	{
		if (execve(cmd->cmd, cmd->arg, shell->envp) == -1)
			perror("execve");
	}
}

t_shell	*init_shell(t_cmd *cmd, t_env **head)
{
	t_shell	*shell;

	//if (!open_files(lex))
	//	return (NULL);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->envp = create_env_arr(head);
	shell->paths = get_paths(shell->envp);
	shell->pid = NULL;
	shell->wstatus = 0;
	execute_cmd(cmd, shell);
	return (shell);
}