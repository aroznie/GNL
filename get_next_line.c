/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: arroznie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 14:32:39 by arroznie     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 21:15:37 by arroznie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		checkline(char **buff, char **line)
{
	char	*bufft;
	char	*endline;

	bufft = *buff;
	if ((endline = ft_strchr(bufft, '\n')) == NULL)
		return (0);
	*endline = '\0';
	*line = ft_strdup(*buff);
	*buff = ft_strdup(endline + 1);
	free(bufft);
	return (1);
}

static int		read_file(int fd, char *temp, char **buff, char **line)
{
	int		nbchar;
	char	*bufft;

	while ((nbchar = read(fd, temp, BUFFER_SIZE)) > 0)
	{
		temp[nbchar] = '\0';
		if (*buff)
		{
			bufft = *buff;
			*buff = ft_strjoin(bufft, temp);
			free(bufft);
		}
		else
			*buff = ft_strdup(temp);
		if (*buff == NULL)
		{
			free(temp);
			return (-1);
		}
		if (checkline(buff, line))
			return (1);
	}
	free(temp);
	return (nbchar);
}

int				get_next_line(int fd, char **line)
{
	static char	*buff;
	char		*temp;
	int			nbchar;

	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (buff)
		if (checkline(&buff, line))
			return (1);
	if (!(temp = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	if ((nbchar = read_file(fd, temp, &buff, line)) == 1)
		free(temp);
	if (buff == NULL || buff[0] == '\0' || nbchar != 0)
	{
		if (nbchar <= 0)
			*line = "";
		return (nbchar);
	}
	*line = buff;
	buff = NULL;
	return (0);
}
