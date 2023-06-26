#ifndef EXPANDER_H
# define EXPANDER_H

# include "types.h"

/* expander 1 */
void	expander_start(t_lexer *lex, t_env *head);
char	*expander(char *input, t_env *head);
char	*deal_with_expansion(char *input, t_env *head);

/* expander 2 - helpers to find correct pathway */
char	*do_expansion_pre(char *input, t_env *head);
char	*do_expansion_pre_with_freeing(char *input, t_env *head);
char	*do_expansion(char *input, t_env *head);
char	*do_expansion_with_freeing(char *input, t_env *head);

/* expander 3 - Expander pathfinder */
char	*replace_string(char *input, t_env *head, char *speci);
char	*expand_home(char *input, t_env *head, char *i);
char	*expand_status(char *input, char *spec, t_env *head);
char	*remove_var_reference(char *input, char *dollar, t_env *head);
char	*expand_env_var(char *input, char *dollar, char *value, t_env *head);

/* expander 4 - expansion utils */
char	*return_key(char *str, t_env *head);
int		return_key_len(char *str);
char	*check_key_exist(t_env *head, char *i);
char	*return_pre_str(char *input, char *speci, t_env *head);
char	*return_post_str(char *key_end, t_env *head);

/* expander 5 -  Expansion utils */
int		check_invalid_follow(char *str);
char	*remove_dollarsign_bef_quotes(char *str, t_env *head);
int		count_dollars(char *input);
char	*ft_strjoin_multiple(char **arr, t_env *head);

/* expander 6 - Splitting by quotes */
char	**split_by_quotes(char *input, t_env *head);
int		ft_count_elements(char *input, char s);
char	**ft_quotesplitter(char **arr, char *input, int count, t_env *head);

/* expander 7 -killing quotes */
char	*kill_quotes(char *expanded, t_env *head);

#endif