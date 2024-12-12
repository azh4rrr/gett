/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azmakhlo <azmakhlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:15:30 by azmakhlo          #+#    #+#             */
/*   Updated: 2024/12/12 17:58:22 by azmakhlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static void	ft_cpy(char **dst, char **src)
{
	int	i;

	i = 0;
	if (*dst && *src)
	{
		while ((*src)[i] && (*src)[i] != '\n')
		{
			(*dst)[i] = (*src)[i];
			i++;
		}
		if ((*src)[i] == '\n')
			(*dst)[i++] = '\n';
		(*dst)[i] = '\0';
	}
}

static char	*get_line(char **buffer)
{
	int		i;
	char	*dst;
	char	*temp;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	dst = malloc(i + 1);
	if (!dst)
		return (ft_free(buffer));
	ft_cpy(&dst, buffer);
	temp = ft_strdup((*buffer) + i);
	if (!temp)
		return (ft_free(buffer), ft_free(&dst));
	ft_free(buffer);
	*buffer = temp;
	return (dst);
}

static char	*ft_get_buffer(int fd, char **buffer)
{
	char	*rd;
	ssize_t	nb;

	rd = malloc(BUFFER_SIZE + 1);
	if (!rd)
		return (ft_free(buffer));
	while (1)
	{
		nb = read(fd, rd, BUFFER_SIZE);
		if (nb < 0 && (!*buffer || !**buffer))
			return (ft_free(buffer), ft_free(&rd));
		rd[nb] = '\0';
		*buffer = ft_strjoin(*buffer, rd);
		if (!*buffer || !buffer)
			return (ft_free(buffer), ft_free(&rd));
		if (ft_strchr(*buffer, '\n') || nb == 0)
			break ;
	}
	ft_free(&rd);
	return (*buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer [OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (ft_free(&buffer[fd]));
	buffer[fd] = ft_get_buffer(fd, &buffer[fd]);
	if (!buffer[fd])
		return (ft_free(&line));
	line = get_line(&buffer[fd]);
	if (!line || ft_strlen(line) == 0)
		return (ft_free(&line), ft_free(&buffer[fd]));
	return (line);
}
