#include "../inc/minishell.h"

int	g_stat;

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