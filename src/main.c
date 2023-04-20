#include "minishell.h"

int	g_stat;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	printf("%s", envp[0]);
	return 0;
}