#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
//values for iterating through num array
typedef enum s_num {
	CMD = 0,
	ARG,
	HERE
}	t_num;

//num array contains number of strings for each part of the struct
//index for num array in t_num struct, e.g. num[HERE] gives you
//the number of heredoc stopwords
typedef struct s_cmd {
	char			*cmd;
	char			**arg;
	int				num[3];
	t_lexer			*in;
	t_lexer			*out;
	char			**here;
	struct s_cmd	*next;
}	t_cmd;

//init functions for parser
t_cmd		*create_parse_list(t_lexer *lex);

//input parsing, creating lists of in/out and more
void		create_words(t_cmd *cmd, t_lexer *lex);
void		count_arg_redir(t_lexer *lex, t_cmd *cmd);

#endif