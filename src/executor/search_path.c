#include "../../inc/minishell.h"

//appends string to existing strings, used for adding / to the end of path
static char	**add_to_string(char **str, char *app)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != NULL)
	{
		tmp = ft_strjoin(str[i], app);
		free(str[i]);
		str[i++] = tmp;
	}
	return (str);
}

//searches through environment variables for path variable
//splits and returns them individually
char	**get_paths(char **envp)
{
	int		i;
	char	**tmp;
	char	*sub;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	sub = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	tmp = ft_split(sub, ':');
	free(sub);
	//tmp = ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5), ':');
	return (add_to_string(tmp, "/"));
}

//F_OK checks if the file exists, X_OK if the file is executable by the proccess
char    *get_cmd_with_path(t_cmd *cmd, char **path)
{
	int     i;
	char    *full_path;

	i = 0;
	full_path = NULL;
	while (path[i] != NULL)
	{
		full_path = ft_strjoin(path[i++], cmd->cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		full_path = safe_free(full_path);
	}
	return (full_path);
}