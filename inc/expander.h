/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:48:15 by rmocsai           #+#    #+#             */
/*   Updated: 2023/05/25 15:29:10 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* expander 1 */
char	**expander_start(char **args, t_env **head);
char	*expander(char *input, t_env **head);
char	*replace_string(char *input, t_env **head, char *i);
char	*remove_var_reference(char *input, char *i);
char	*expand_home(char *input, t_env **head, char *i);

/* expander 2 - helpers */
char	*return_key(char *str);
int		return_key_len(char *str);
int		return_value_len(char *str);
char	*check_key_exist(t_env **head, char *i);
char	*expand_env_var(char *input, char *dollar, char *value);

/* expander 3 - helpers to reproduce new str */
char	*return_pre_str(char *input, char *spec);
char	*return_post_str(char *key_end);
t_env	*create_home(char *str, t_env **head);

#endif