#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>

/* global variable for exit status */
extern int	g_stat;

/* Struct for nodes */
typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

/* Struct For Environment List */
typedef struct s_env
{
	struct s_env_node	*head;
	int					size;
}	t_env;

#endif
