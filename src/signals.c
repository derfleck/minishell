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
	else if (i == PARENT)
	{
		signal(SIGINT, handle_signals_child);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == -1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
