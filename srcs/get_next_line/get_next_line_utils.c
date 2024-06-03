/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:31:07 by omfelk            #+#    #+#             */
/*   Updated: 2024/01/29 15:45:57 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_str_join(char *left_text, char *buff, int byte_read)
{
	char		*new_left_text;
	int			i;
	int			j;
	size_t		total;

	i = -1;
	j = -1;
	if (!left_text && !buff)
		return (NULL);
	if (!left_text)
		left_text = ft_calloc(sizeof(char), 1);
	total = ft_strlen(left_text) + ft_strlen(buff) + 1;
	new_left_text = ft_calloc(sizeof(char), total);
	if (!new_left_text)
		return (NULL);
	while (left_text[++i] != '\0')
		new_left_text[i] = left_text[i];
	while (++j < byte_read)
		new_left_text[i++] = buff[j];
	free(left_text);
	return (new_left_text);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*get(char *text_line)
{
	char	*get_line_final;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (text_line[i] != '\0' && text_line[i] != '\n')
		i++;
	get_line_final = ft_calloc(sizeof(char), i + 2);
	if (!get_line_final)
		return (NULL);
	while (j <= i)
	{
		get_line_final[j] = text_line[j];
		j++;
	}
	free(text_line);
	return (get_line_final);
}

char	*get_left(char *text_line)
{
	char	*left_get;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (text_line[i] != '\0' && text_line[i] != '\n')
		i++;
	if (text_line[i] == '\n')
	{
		j = i;
		while (text_line[j] != '\0')
			j++;
		left_get = ft_calloc(sizeof(char), (j - i) + 1);
		if (!left_get)
			return (NULL);
		left_get[(j - i)] = '\0';
		j = 0;
		i++;
		while (text_line[i] != '\0')
			left_get[j++] = text_line[i++];
		return (left_get);
	}
	return (NULL);
}
