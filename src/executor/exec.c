#include "../../inc/minishell.h"

//checks if command is a builtin
int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 3) == 0 || \
		ft_strncmp(cmd, "env", 3) == 0 || \
		ft_strncmp(cmd, "cd", 2) == 0 || \
		ft_strncmp(cmd, "export", 6) == 0 || \
		ft_strncmp(cmd, "unset", 5) == 0 || \
		ft_strncmp(cmd, "exit", 4) == 0 || \
		ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else
		return (0);
}

//TODO: set correct status code
static void	mini_pathfinder(t_shell *sh, t_cmd *cmd, t_env **env, int mode)
{
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		g_stat = builtin_pwd(*env);
	else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		g_stat = builtin_env(*env, &cmd->arg[1]);
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		g_stat = builtin_cd(&cmd->arg[1], env);
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		g_stat = builtin_export(&cmd->arg[1], env);
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
		g_stat = builtin_unset(&cmd->arg[1], env);
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		g_stat = builtin_echo(&cmd->arg[1], *env);
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		g_stat = builtin_exit(sh, &cmd->arg[1], env, mode);
	if (mode == CHILD)
	{
		free_env_list(env);
		free_shell(sh);
		exit(g_stat);
	}
}

//helper function, checks the absolute size in bytes of the
//environment variables, doesn't return if too big, 1 if pass
static int	check_environ_size(t_shell *shell, t_env **head, char *cmd)
{
	size_t	size;
	t_env	*tmp;

	size = 0;
	if (is_builtin(cmd) && ft_strncmp(cmd, "env", 3))
		return (1);
	tmp = *head;
	while (tmp)
	{
		size += ft_strlen(tmp->key_value + 1);
		tmp = tmp->next;
	}
	if (size > ARG_MAX)
		perror_env_too_big(cmd, shell, head);
	return (1);
}

//checks if a path is a file or directory
//prints error and exits with 126 when directory
int	check_file_dir(char *path, t_shell *sh, t_env **head)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		perror("stat");
	if (S_ISREG(st.st_mode))
		return (0);
	else if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		if (head)
			free_env_list(head);
		if (sh)
			free_shell(sh);
		g_stat = 126;
		exit(126);
	}
	else
		return (1);
}

//checks if command path is absolute or relative
void	execute_cmd(t_cmd *cmd, t_shell *shell, t_env **head, int mode)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->cmd == NULL)
		return ;
	if (check_environ_size(shell, head, cmd->cmd) && ft_strcmp(".", cmd->cmd))
		perror_exit_2("source alias not supported\n", shell, head, mode);
	else if (ft_strncmp("./", cmd->cmd, 2) == 0 || is_builtin(cmd->cmd))
	{
		if (is_builtin(cmd->cmd))
			mini_pathfinder(shell, cmd, head, mode);
		else if (check_file_dir(cmd->cmd, shell, head))
			return ;
		else if (execve(cmd->cmd, cmd->arg, shell->envp) == -1)
			perror("execve");
	}
	else
	{
		tmp = get_cmd_with_path(cmd, shell->paths);
		if (!tmp)
			perror_cmd_not_found(cmd->cmd, shell);
		if (execve(tmp, cmd->arg, shell->envp) == -1)
			perror("execve");
		free(tmp);
	}
}

//initializes shell struct containing environment variables
//and extracted paths from PATH variable, if it exists
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
