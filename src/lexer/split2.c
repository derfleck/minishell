#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	tab = malloc((sizeof(char) * i) + 1);
	if (!tab)
		return (0);
	while (s[j] != '\0')
	{
		*(tab + j) = *(s + j);
		j++;
	}
	*(tab + j) = '\0';
	return (tab);
}

static char	*ft_toolarge(void)
{
	char	*sub;

	sub = malloc(sizeof(char) * 1);
	if (!sub)
		return (NULL);
	sub[0] = '\0';
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;
	size_t	l;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start >= l)
		return (ft_toolarge());
	while (s[start + i] != '\0' && i < (unsigned int) len)
		i++;
	sub = malloc((sizeof(char) * i) + 1);
	if (!sub)
		return (NULL);
	while (j < i)
	{
		sub[j] = s[start + j];
		j++;
	}
	sub[j] = '\0';
	return (sub);
}

static int	ft_checksep(char const s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	if (*set == '\0')
		return (ft_strdup(s1));
	while (ft_checksep(*s1, set) == 1)
		s1++;
	len = (size_t) ft_strlen(s1);
	while (ft_checksep(s1[len - 1], set) == 1 && len)
		len--;
	return (ft_substr(s1, 0, len));
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	else
		return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	val;

	val = nmemb * size;
	if (nmemb != 0 && val / nmemb != size)
		return (NULL);
	ptr = malloc(val);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, val);
	return ((void *)ptr);
}

int	skip_quotes(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
	{
		while (str[++i] && str[i] != '\'')
			;
	}
	if (str[i] == '"')
	{
		while (str[++i] && str[i] != '"')
			;
	}
	return (i);
}

//new part after here
int	cnt_cmd(char *str, char *set)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strtrim(str, set);
	j = 0;
	while (*tmp)
	{
		i = skip_quotes(tmp);
		while (ft_strchr(set, tmp[i]) == 0 && \
				(tmp[i] != '\'' || tmp[i] != '"'))
			i++;
		if (i)
			j++;
		else
		{
			while (ft_strchr(set, tmp[i]) != 0)
				i++;
		}
		tmp += i;
	}
	return (j);
}

char	**split_lexer(char *str, char *set)
{
	int		i;
	int		j;
	char	*tmp;
	char	**split;

	tmp = ft_strtrim(str, set);
	j = 0;
	split = ft_calloc(sizeof(char *), cnt_cmd(str, set) + 1);
	while (*tmp)
	{
		i = skip_quotes(tmp);
		while (ft_strchr(set, tmp[i]) == 0 && \
				(tmp[i] != '\'' || tmp[i] != '"'))
			i++;
		if (i)
			split[j++] = ft_substr(tmp, 0, i);
		else
		{
			while (ft_strchr(set, tmp[i]) != 0)
				i++;
		}
		tmp += i;
	}
	return (split);
}

int		main(void)
{
	char	**test;
	int		i = 0;
	char *new = "\"Das ist |ein Test \" | \"  \"    Test\" \'Noch ein Test\'\"";
	char *set = " ";

	test = split_lexer(new, set);
	while (test[i])
	{
		printf("%i ", i);
		printf("%s\n", test[i]);
		i++;
	}
	return (0);
}