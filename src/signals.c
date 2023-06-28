#include "../inc/minishell.h"

/* Child process handler of signal types SIGINT(ctrlC) and SIGQUIT(ctrl\)*/
void	handle_signals_child(int signum)
{
	if (signum == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_stat = 130;
	}
	else if (signum == SIGQUIT)
	{
		//ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		printf("Quit (core dumped)\n");
		//g_stat = 131;
	}
}

/* Checks if process is running as parent (main process) or as child.
For this we need to keep track what's going on -> id them or use pid? */
void	set_sigaction(int i)

{
	if (i == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (i > CHILD)
	{
		signal(SIGINT, handle_signals_child);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
