#include "../../includes/minishell.h"


t_list	*ft_add(char *line, int start, int end, int type)
{
	t_list	*new;
    int     i;
    int     j;
    
    i = 0;
    j = start;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
        end++;
    new->str =  (char *)malloc(sizeof(char) * (end - start) + 1);
    while (j < end)
    {
        new->str[i] = line[j];
        i++;
        j++;
    }
    new->type = type;
    new->len = i;
    new->str[i] = '\0';
	new->next = NULL;
	return (new);
}

char	*ft_strjoin_n(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (s1);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}

char	*ft_strdup_n(char *src)
{
	char	*t;
	int		i;
	int		j;

	i = ft_strlen(src);
	if(!src)
		return (NULL);
	t = (char *)malloc(i + 1 * sizeof(char));
	if (t == NULL)
		return (NULL);
	j = 0;
	while (src[j] != '\0')
	{
		t[j] = src[j];
		j++;
	}
	t[j] = '\0';
	return (t);
}