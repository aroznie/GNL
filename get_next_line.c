/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: arroznie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 14:32:39 by arroznie     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 16:49:16 by arroznie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		checkline(char **buff, char **line)
{
	char	*bufft; /* buff temporaire */
	char	*endline; /* position du '\n' */

	bufft = *buff;
	if ((endline = ft_strchr(bufft, '\n')) == NULL) /* endline prend la position du '\n' */
		return (0);
	*endline = '\0'; /* transforme le '\n' en '\0' */
	*line = ft_strdup(*buff); /* line garde en memoire le buffer */
	*buff = ft_strdup(endline + 1); /* le buffer devient le temp a lire */
	free(bufft); /* on libere la memoire du bufftemp */
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

	if (!line || fd < 0 || fd > FD_SETSIZE || BUFFER_SIZE < 1)
		return (-1); /* Gestion d'erreur */
	if (buff) /* check si un buff existe deja */
		if (checkline(&buff, line))
			return (1);
	if (!(temp = malloc(sizeof(char) * BUFFER_SIZE + 1))) /* alloue la memoire de temp qui prends la taille du buffer */
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

#include <stdio.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include "get_next_line.h"
#include <string.h>


int main(int argc, char **argv)
{
	int fd;
	int ret;
	int line;
	char *buff;

	line = 0;
	ret = 1;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (ret > 0)
		{
			if ((ret = get_next_line(fd, &buff)) > 0 || buff)
			{
				printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
				if (strcmp("", buff) != 0 || ret)
					free(buff);
			}
		}
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of file\n");
		close(fd);
	}
	if (argc == 1)
	{
		while ((ret = get_next_line(0, &buff)) > 0)
			printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of stdin\n");
		close(fd);
	}
	return (0);
}
