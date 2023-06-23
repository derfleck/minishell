#include "../inc/minishell.h"

/* Handle conrol+C signal SIGINT in the parent process. prints newline, empties RL buffer and redisplays prompt
If parent process receives control+\ it ignores it with SIG_IGN */
void	handle_ctrlc(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_stat = 130;
		/*
		write(STDOUT_FILENO, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		*/
	}
}

/* Child process handler of signal types SIGINT(ctrlC) and SIGQUIT(ctrl\)
Not sure if it's working, but we can only test if we have multiple processes  */
void	handle_signals_child(int signum)
{
	printf("%d\n", signum);
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_stat = 130;
	}
	if (signum == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
		g_stat = 131;
	}
}

/* Checks if process is running as parent (main process) or as child (after fork).
For this we need to keep track what's going on -> id them or use pid? */
void	set_sigaction(int i)

{
	if (i >= CHILD)
	{
		signal(SIGINT, handle_signals_child);
		signal(SIGQUIT, handle_signals_child);
	}
	else if (i > CHILD)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_ctrlc);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
