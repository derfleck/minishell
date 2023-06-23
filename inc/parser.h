#ifndef PARSER_H
# define PARSER_H

# include "types.h"

//init functions for parser
t_cmd	*create_parse_list(t_lexer *lex, t_env *env);

//input parsing, creating lists of in/out and more
int		create_words(t_cmd *cmd, t_lexer *lex);
void	count_arg_redir(t_lexer *lex, t_cmd *cmd);

#endif