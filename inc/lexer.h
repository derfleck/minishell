#ifndef LEXER_H
# define LEXER_H

# include "types.h"

//functions for lexer
t_type		classify_token(char	*str);
t_type		check_token(char c);
int			syntax_check(char *str);
int			count_char(char *str, char c);
int			skip_quotes(char *str);

//functions for splitting line
void		empty_set(char **str);
char		**ft_split_set(char *str, char *set);

//functions for creating lexer list
t_lexer		*start_lexer(char *str, t_env *env);

#endif