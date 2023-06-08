/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:48:15 by rmocsai           #+#    #+#             */
/*   Updated: 2023/06/08 12:22:17 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* expander 1 */
char	**expander_start(char **args, t_env *head);
char	*expander(char *input, t_env *head);
char	*deal_with_expansion(char *input, t_env *head);
char	*expand_parts(char *input, t_env *head, int start, int end);


/* expander 2 - helpers */
char	*return_key(char *str);
int		return_key_len(char *str);
// int		return_value_len(char *str);
char	*check_key_exist(t_env *head, char *i);

/* expander 3 - helpers to reproduce new str */
char	*return_pre_str(char *input, char *speci);
char	*return_post_str(char *key_end);
t_env	*create_home(char *str, t_env *head);

/* expander 4 -helpers */
char	*replace_string(char *input, t_env *head, char *speci);
char	*remove_var_reference(char *input, char *i);
char	*expand_home(char *input, t_env *head, char *i);
char	*expand_env_var(char *input, char *dollar, char *value);

/* expander 5 -killing quotes */
char	*kill_quotes(char *expanded);
char	*remove_quotes(char *input, int start, int end, char c);
char	*create_quote_free_str(char *input, int start, int end, char c);
int		return_quote_len(char *start, char c);
int		found_quotes(char *input);

/* expander 6 - Splitting by quotes */
int		ft_count_elements(char *input, char s);
char	**split_by_quotes(char *input, t_env *head);
char	*ft_strjoin_multiple(char **arr);
char	**ft_quotesplitter(char **arr, char *input, int count);
char	*do_expansion(char *input, t_env *head);
int		need_to_expand(char *input);
#endif