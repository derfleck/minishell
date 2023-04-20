#include "../inc/minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

static int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

char	*prompt_line(void)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strjoin(getenv("USER"), "@minishell:");
	tmp2 = getcwd(NULL, 0);
	if (ft_strcmp(tmp2, getenv("HOME")))
	{
		free(tmp2);
		return (ft_strjoin(tmp, "~$"));
	}
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp3, "$");
	free(tmp3);
	return (tmp);
}

void	get_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	free(buf);
}

int	main(void)
{
	char	*s;

	while (1)
	{
		s = readline(prompt_line());
		if (ft_strcmp(s, "pwd"))
			get_pwd();
		else
			printf("%s\n", s);
		free(s);
	}
	return (0);
}

/*
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	printf("%s\n", envp[5]);
	while (1)
	{
		continue ;	
	}
	return (0);
}
*/
