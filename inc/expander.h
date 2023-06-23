#ifndef EXPANDER_H
# define EXPANDER_H

# include "types.h"

/* expander 1 */
//char	**expander_start(char **args, t_env *head);
void	expander_start(t_lexer *lex, t_env *head);
char	*expander(char *input, t_env *head);
char	*deal_with_expansion(char *input, t_env *head);
char	*do_expansion_pre(char *input, t_env *head);
char	*do_expansion_pre_with_freeing(char *input, t_env *head);
char	*do_expansion(char *input, t_env *head);
char	*do_expansion_with_freeing(char *input, t_env *head);
char	**split_by_dollars(char *input, t_env *head, int i);

/* expander 2 - expansion helpers */
char	*return_key(char *str, t_env *head);
int		return_key_len(char *str);
char	*check_key_exist(t_env *head, char *i);
char	*return_pre_str(char *input, char *speci, t_env *head);
char	*return_post_str(char *key_end, t_env *head);

/* expander 3 - helpers to reproduce new str */
char	**split_by_quotes(char *input, t_env *head);
int		ft_count_elements(char *input, char s);
char	**ft_quotesplitter(char **arr, char *input, int count, t_env *head);
char	*ft_strjoin_multiple(char **arr, t_env *head);

/* expander 4 -helpers */
char	*remove_var_reference(char *input, char *dollar, t_env *head);
char	*replace_string(char *input, t_env *head, char *speci);
char	*expand_home(char *input, t_env *head, char *i);
char	*expand_env_var(char *input, char *dollar, char *value, t_env *head);
t_env	*create_home(char *str, t_env **head);

/* expander 5 -killing quotes */
char	*kill_quotes(char *expanded, t_env *head);
char	*remove_quotes(char *input, int start, int end, t_env *head);
char	*create_quote_free_str(char *input, int start, int end, t_env *head);
int		return_quote_len(char *start, char c);
int		found_quotes(char *input);

/* expander 6 - Splitting by quotes */
int		need_to_expand(char *input);
int		check_invalid_follow(char *str);
char	*remove_dollarsign_bef_quotes(char *str, t_env *head);
char	*expand_status(char *input, char *spec, t_env *head);
int		count_dollars(char *input);

#endif