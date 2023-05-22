#include "../../inc/minishell.h"

//iterates through 2D array till first occurence of NULL
int	move_to_empty(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

//allocates memory for the pieces of the t_cmd struct
//TODO: add error for malloc fail
void	init_cmd_struct(t_cmd *cmd)
{
	cmd->in = malloc(sizeof(t_in));
	if (!cmd->in)
		return ;
	cmd->out = malloc(sizeof(t_out));
	if (!cmd->out)
		return ;
	cmd->out->last = NULL;
	cmd->in->last = NULL;
	cmd->arg = ft_calloc(cmd->num[ARG] + 1, sizeof(char *));
	if (!cmd->arg)
		return ;
	cmd->in->input = ft_calloc(cmd->num[IN] + 1, sizeof(char *));
	if (!cmd->in->input)
		return ;
	cmd->out->output = ft_calloc(cmd->num[OUT] + 1, sizeof(char *));
	if (!cmd->out->output)
		return ;
	cmd->out->append = ft_calloc(cmd->num[APP] + 1, sizeof(char *));
	if (!cmd->out->append)
		return ;
	cmd->in->here = ft_calloc(cmd->num[HERE] + 1, sizeof(char *));
	if (!cmd->in->here)
		return ;
}
