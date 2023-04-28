#include "../inc/minishell.h"

void	handle_ctrlc(int signum)
{
	if (signum == SIGINT)
	{
		g_stat = 130;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals_child(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_stat = 130;
	}
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_stat = 131;
	}
}

void	set_sigaction(int i)

{
	if (i == PARENT)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_ctrlc);
	}
	if (i == CHILD)
	{
		signal(SIGINT, handle_signals_child);
		signal(SIGQUIT, handle_signals_child);
	}
}
