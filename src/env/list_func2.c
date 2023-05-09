#include "../../inc/minishell.h"

char	*split_env_value(char *str)
{
	if (!str)
		return (NULL);
	while (*str != '=' && str)
		str++;
	str++;
	if (!str)
		return (NULL);
	return (str);
}

char	*split_env_key(const char *str)
{
	size_t		i;
	char		*key;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '=' && str)
		i++;
	key = ft_substr(str, 0, i);
	if (!key)
		perror("Malloc failed");
	return (key);
}
//TODO free key somewhere!!!
//or alternatively a no-malloc option:
// char	*split_env_key(const char *str)
// {
// 	size_t			i;
// 	static char		key[250];

// 	i = 0;
// 	if (!str)
// 		return (NULL);
// 	while (str[i] != '=' && str)
// 		i++;
// 	ft_memmove(key, str, i);
// 	key[(int)i] = '\0';
// 	return (key);
// }
