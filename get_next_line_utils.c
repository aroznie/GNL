/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: arroznie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 16:05:59 by arroznie     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/21 03:57:22 by arroznie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s1;

	i = 0;
	s1 = (char *)s;
	while (s1[i])
	{
		if (s1[i] == c)
			return (s1 + i);
		i++;
	}
	if (s1[i] == c)
		return (s1 + i);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = ft_strlen(s1);
	i++;
	if (!(s2 = malloc(sizeof(char) * i)))
		return (NULL);
	while (i > 0)
	{
		s2[i - 1] = s1[i - 1];
		i--;
	}
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*s3;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = 0;
	if (!(s3 = malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	while (k < (i + j))
	{
		if (k < i)
			s3[k] = s1[k];
		else
			s3[k] = s2[k - i];
		k++;
	}
	s3[k] = '\0';
	return (s3);
}
