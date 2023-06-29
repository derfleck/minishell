#include "../../inc/minishell.h"

//creates new linked list for lexer, needs token count
static t_lexer	*new_lexer_list(char **cmd, int i)
{
	int		j;
	t_lexer	*lex;

	j = 0;
	lex = ft_calloc(i, sizeof(t_lexer));
	if (!lex)
		return (NULL);
	while (cmd[j])
	{
		lex[j].i = j;
		lex[j].str = cmd[j];
		lex[j].token = classify_token(cmd[j]);
		if (j < i - 1)
			lex[j].next = (lex + j + 1);
		else
			lex[j].next = NULL;
		if (j == 0)
			lex[j].prev = NULL;
		else
			lex[j].prev = (lex + j - 1);
		j++;
	}
	return (lex);
}

//helper, removes set characters from beginning and end of string
//required to split safely
static char	*trim_string(char *str, char *set)
{
	char	*tmp;

	tmp = ft_strtrim(str, set);
	if (!tmp)
	{
		perror("Error trimming string\n");
		return (NULL);
	}
	else if (tmp && tmp[0] == '\0')
	{
		tmp = free_ptr(tmp);
		return (NULL);
	}
	return (tmp);
}

static char	*syntax_trimming_helper(char *str, char *set)
{
	char	*tmp;

	if (str && !syntax_check(str))
	{
		ft_putendl_fd("Syntax error: quotes unclosed", STDERR_FILENO);
		g_stat = 2;
		free(str);
		return (NULL);
	}
	tmp = trim_string(str, set);
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	return (tmp);
}

//starts the lexer
t_lexer	*start_lexer(char *str, t_env *env)
{
	int			i;
	char		**split;
	char		*tmp;
	t_lexer		*lex;
	static char	set[6] = " \t\n\v\f\r";

	i = 0;
	tmp = syntax_trimming_helper(str, set);
	if (!tmp)
		return (NULL);
	split = ft_split_set(tmp, set);
	free(tmp);
	if (!split)
		perror_lexer("Error splitting string\n", str, env, NULL);
	while (split[i])
		i++;
	lex = new_lexer_list(split, i);
	split = free_ptr(split);
	if (!lex)
		perror_lexer("Error creating lexer list\n", str, env, lex);
	return (lex);
}
