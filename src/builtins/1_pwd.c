#include "../../inc/minishell.h"

/* gets the current working directory and prints it on the screen */
void	builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	free(buf);
	g_stat = 0;
}

/* Counts how many arguments are in the array to deal with */
int	helper_get_arg_count(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
