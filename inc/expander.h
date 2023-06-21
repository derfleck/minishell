#ifndef EXPANDER_H
# define EXPANDER_H

# include "types.h"

/* expander 1 */
//char	**expander_start(char **args, t_env *head);
void	expander_start(t_lexer *lex, t_env *head);
char	*expander(char *input, t_env *head);
char	*deal_with_expansion(char *input, t_env *head);
char	*do_expansion(char *input, t_env *head);
char	**split_by_quotes(char *input, t_env *head);

/* expander 2 - expansion helpers */
char	*return_key(char *str);
int		return_key_len(char *str);
char	*check_key_exist(t_env *head, char *i);
char	*return_pre_str(char *input, char *speci);
char	*return_post_str(char *key_end);

/* expander 3 - helpers to reproduce new str */
int		need_to_expand(char *input);
int		ft_count_elements(char *input, char s);
char	**ft_quotesplitter(char **arr, char *input, int count);
char	*ft_strjoin_multiple(char **arr);

/* expander 4 -helpers */
char	*replace_string(char *input, t_env *head, char *speci);
char	*remove_var_reference(char *input, char *i);
char	*expand_home(char *input, t_env *head, char *i);
char	*expand_env_var(char *input, char *dollar, char *value);
t_env	*create_home(char *str, t_env **head);

/* expander 5 -killing quotes */
char	*kill_quotes(char *expanded);
char	*remove_quotes(char *input, int start, int end, char c);
char	*create_quote_free_str(char *input, int start, int end, char c);
int		return_quote_len(char *start, char c);
int		found_quotes(char *input);

/* expander 6 - Splitting by quotes */
char	*remove_dollarsign_bef_quotes(char *str);
int		check_invalid_follow(char *str);
char	*expand_status(char *input, char *spec);

#endif