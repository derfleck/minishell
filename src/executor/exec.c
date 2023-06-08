#include "../../inc/minishell.h"

//checks if command is a builtin
static int	is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 || \
		ft_strncmp(cmd->cmd, "env", 3) == 0 || \
		ft_strncmp(cmd->cmd, "cd", 2) == 0 || \
		ft_strncmp(cmd->cmd, "export", 6) == 0 || \
		ft_strncmp(cmd->cmd, "unset", 5) == 0 || \
		ft_strncmp(cmd->cmd, "echo", 4) == 0)
		return (1);
	else
		return (0);
}

//TODO: set correct status code
static void	mini_pathfinder(t_cmd *cmd, t_env *env)
{
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		builtin_pwd();
	else if(ft_strncmp(cmd->cmd, "env", 3) == 0)
		print_env(env);
	else if(ft_strncmp(cmd->cmd, "cd", 2) == 0)
		builtin_cd(&cmd->arg[1], env);
	else if(ft_strncmp(cmd->cmd, "export", 6) == 0)
		builtin_export(&cmd->arg[1], env);
	else if(ft_strncmp(cmd->cmd, "unset", 5) == 0)
		builtin_unset(&cmd->arg[1], env);
	else if(ft_strncmp(cmd->cmd, "echo", 4) == 0)
		builtin_echo(&cmd->arg[1], env);
	exit(0);
}

//checks if command path is absolute or relative
void	execute_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->cmd == NULL)
		return ;
	if (cmd->cmd && ft_strncmp("./", cmd->cmd, 2) != 0 && !is_builtin(cmd))
	{
		tmp = get_cmd_with_path(cmd, shell->paths);
		if (!tmp)
		{
			printf("%s: command not found\n", cmd->cmd);
			return ;
		}
		if (execve(tmp, cmd->arg, shell->envp) == -1)
			perror("execve");
		free(tmp);
	}
	else
	{
		if (is_builtin(cmd))
			mini_pathfinder(cmd, shell->env);
		else if (execve(cmd->cmd, cmd->arg, shell->envp) == -1)
			perror("execve");
	}
}

//initializes shell struct containing environment variables
//and extracted paths from PATH variable, if it exists
t_shell	*init_shell(t_cmd *cmd, t_env *head)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->envp = create_env_arr(head);
	shell->paths = get_paths(shell->envp);
	shell->pid = ft_calloc(cmd->num[CMD], sizeof(pid_t));
	if (!shell->pid)
		return (NULL);
	shell->env = head;
	shell->wstatus = 0;
	if (cmd->num[CMD] > 1)
	{
		if (!cmd_with_pipes(shell, cmd))
			return (NULL);
	}
	else
		exec_single_cmd(cmd, shell);
	cmd->start = free_lex(cmd->start);
	cmd = free_cmd(cmd);
	return (safe_free(shell));
}
