#include "../inc/minishell.h"

int	ft_isnum(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
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

char	*safe_join(char *s1, char *s2, t_env *head)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		perror_exit_free_env("Malloc failed\n", head);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (ret);
}
