/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:05:05 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/05 22:26:16 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FDMAX
#  define FDMAX 24576
# endif

# include <stdlib.h>
# include <unistd.h>

char	*ft_strcat(char *dest, const char *src);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);

char	*get_next_line(int fd);
int		reader_terminator(char **buffer, char **line);
char	*reader_wrapper(int fd, char **buffer);
int		reader(int fd, char **buffer, char **line);
void	formatter(char **buffer, char **line);

#endif