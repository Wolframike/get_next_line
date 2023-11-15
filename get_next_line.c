/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:01:28 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/06 01:52:52 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	formatter(char **buffer, char **line)
{
	size_t	l;
	char	*tmp;

	l = 0;
	while ((*buffer)[l] != '\n' && (*buffer)[l] != '\0')
		l++;
	l++;
	*line = (char *)malloc(sizeof(char) * (l + 1));
	if (*line == NULL)
		return ;
	(*line)[l] = '\0';
	while (l-- > 0)
		(*line)[l] = (*buffer)[l];
	if (ft_strchr(*buffer, '\n') != NULL)
	{
		tmp = ft_strdup(ft_strchr(*buffer, '\n') + 1);
		free(*buffer);
		*buffer = tmp;
	}
	else
	{
		free(*buffer);
		*buffer = ft_strdup("\0");
	}
}

int	reader_terminator(char **buffer, char **line)
{
	formatter(buffer, line);
	if (*buffer == NULL)
		return (-1);
	return (1);
}

int	reader(int fd, char **buffer, char **line)
{
	ssize_t	rsize;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (tmp == NULL)
		return (-1);
	rsize = 42;
	while (rsize > 0 && !ft_strchr(*buffer, '\n'))
	{
		rsize = read(fd, tmp, BUFFER_SIZE);
		if ((rsize == -1) || (rsize == 0 && ft_strlen(*buffer) == 0))
		{
			free(tmp);
			return (rsize);
		}
		tmp[rsize] = '\0';
		*buffer = ft_strjoin(*buffer, tmp);
		if (*buffer == NULL)
		{
			free(tmp);
			return (-1);
		}
	}
	free(tmp);
	return (reader_terminator(buffer, line));
}

char	*reader_wrapper(int fd, char **buffer)
{
	char	*line;
	int		exstatus;

	line = NULL;
	exstatus = reader(fd, buffer, &line);
	if ((exstatus == 0 && *buffer != NULL) || exstatus == -1)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (exstatus != 1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FDMAX + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FDMAX || read(fd, 0, 0) < 0)
		return (NULL);
	if (buffer[fd] == NULL)
	{
		buffer[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer[fd] == NULL)
			return (NULL);
		buffer[fd][0] = '\0';
	}
	return (reader_wrapper(fd, &buffer[fd]));
}
