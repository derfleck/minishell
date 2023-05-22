#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
//values for iterating through num array
typedef enum s_num {
	CMD = 0,
	ARG,
	IN,
	OUT,
	APP,
	HERE
}	t_num;

typedef struct s_out {
	char	**output;
	char	**append;
	t_lexer	*last;
}	t_out;

typedef struct s_in {
	char	**input;
	char	**here;
	t_lexer	*last;
}	t_in;

//num array contains number of strings for each part of the struct
//index for num array in t_num struct, e.g. num[HERE] gives you
//the number of heredoc stopwords
typedef struct s_cmd {
	char			*cmd;
	char			**arg;
	int				num[6];
	t_out			*out;
	t_in			*in;
	struct s_cmd	*next;
}	t_cmd;

//init functions for parser
t_cmd		*create_parse_list(t_lexer *lex);

//input parsing, creating lists of in/out and more
void		create_words(t_cmd *cmd, t_lexer *lex);
t_lexer		*count_arg_redir(t_lexer *lex, t_cmd *cmd);
void		handle_in_out(t_cmd *cmd, t_lexer *lex);

//utils for parser
void		init_cmd_struct(t_cmd *cmd);
void		assign_word(t_cmd *cmd, t_lexer *lex);
int			move_to_empty(char **str);

#endif