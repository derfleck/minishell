#include "../../inc/minishell.h"

//checks if command is a builtin
int	is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 || \
		ft_strncmp(cmd->cmd, "env", 3) == 0 || \
		ft_strncmp(cmd->cmd, "cd", 2) == 0 || \
		ft_strncmp(cmd->cmd, "export", 6) == 0 || \
		ft_strncmp(cmd->cmd, "unset", 5) == 0 || \
		ft_strncmp(cmd->cmd, "exit", 4) == 0 || \
		ft_strncmp(cmd->cmd, "echo", 4) == 0)
		return (1);
	else
		return (0);
}

//TODO: set correct status code
static void	mini_pathfinder(t_shell *sh, t_cmd *cmd, t_env **env, int mode)
{
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		builtin_pwd(*env);
	else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		print_env(*env);
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		builtin_cd(&cmd->arg[1], *env);
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		builtin_export(&cmd->arg[1], *env);
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
	{
		builtin_unset(&cmd->arg[1], env);
		sh->head = *env;
	}
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		builtin_echo(&cmd->arg[1], *env);
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		builtin_exit(sh, &cmd->arg[1], env, mode);
	if (mode == CHILD)
	{
		free_env_list(env);
		free_shell(sh);
		exit(0);
	}
}

//checks if command path is absolute or relative
void	execute_cmd(t_cmd *cmd, t_shell *shell, t_env **head, int mode)
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
			free_shell(shell);
			exit(g_stat = 127);
		}
		if (execve(tmp, cmd->arg, shell->envp) == -1)
			perror("Error when executing\n");
		free(tmp);
	}
	else
	{
		if (is_builtin(cmd))
			mini_pathfinder(shell, cmd, head, mode);
		else if (execve(cmd->cmd, cmd->arg, shell->envp) == -1)
			perror("Error when executing\n");
	}
}

//initializes shell struct containing environment variables
//and extracted paths from PATH variable, if it exists
//TODO: remove t_shell return type, change to void
void	init_shell(char *s, t_cmd *cmd, t_env **head)
{
	t_shell	*shell;

	cmd->cmd = cmd->arg[0];
	shell = malloc(sizeof(t_shell));
	if (!shell)
		perror_cmd("Error initializing shell\n", cmd, *head);
	shell->cmd_start = cmd;
	shell->head = *head;
	shell->wstatus = 0;
	shell->s = s;
	shell->envp = create_env_arr(*head);
	shell->paths = get_paths(shell->envp);
	shell->pid = ft_calloc(cmd->num[CMD] + 1, sizeof(pid_t));
	if (!shell->pid)
		perror_shell("Error initializing shell\n", shell);
	if (cmd->num[CMD] > 1)
		cmd_with_pipes(shell, cmd, head);
	else
		exec_single_cmd(cmd, shell, head);
}
