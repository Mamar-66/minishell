/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:35:29 by omfelk            #+#    #+#             */
/*   Updated: 2024/01/29 18:25:01 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *left_text)
{
	char	*buff;
	int		byte_read;

	buff = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (1)
	{
		ft_bzero(buff, '\0');
		byte_read = read(fd, buff, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buff);
			return (NULL);
		}
		if ((byte_read == 0 && buff[0] == '\0'))
			break ;
		left_text = ft_str_join(left_text, buff, byte_read);
		if (ft_strchr(left_text, '\n') || byte_read == 0)
			break ;
	}
	free(buff);
	return (left_text);
}

char	*get_next_line(int fd)
{
	char		*text_line;
	static char	*left_text;

	text_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (left_text)
			free(left_text);
		return (NULL);
	}
	text_line = read_line(fd, left_text);
	if (!text_line)
	{
		left_text = NULL;
		return (NULL);
	}
	if (text_line[0] == '\0')
	{
		free(left_text);
		return (NULL);
	}
	left_text = get_left(text_line);
	text_line = get(text_line);
	return (text_line);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && count * size / size != count)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tab;
	size_t			i;

	tab = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		tab[i] = 0;
		i++;
	}
	s = tab;
}
