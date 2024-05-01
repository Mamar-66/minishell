/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:51:38 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/01 17:29:41 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static	void	gest_guillemets(bool *guillemets)
// {

// }

// static	void	double_redirect_right(char *str, int *start, bool *redirect)
// {
// 	char	*file_name;
// 	int		fd;
// 	int 	i;

// 	i = *start;
// 	if (str[i] == '>' && str[i + 1] == '\0')
// 		i++;
// 	else
// 	{
// 		while (str[i] != '>' && str[i])
// 			i++;
// 		i += 2;
// 	}
// 	file_name = recover_word(str + i, 1, false);
// 	fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
// 	while (&str[i] != ft_strchr(str + *start, *file_name))
// 		i++;
// 	i += ft_strlen(file_name);
// 	*start = i - 1;
// 	*redirect = true;
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// }

static	char	*redirect_right(char *str, int *start)
{
	char	*return_str;
	char	c[2];
	char	*file_name;
	int		fd;
	int 	i;

	i = *start;
	c[0] = 127;
	c[1] = '\0';
	return_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '>')
		{
			str[i++] = 127;
			break ;
		}
		c[0] = str[i];
		return_str = ft_strjoin(return_str, c);
		i++;
	}
	file_name = recover_word(str + i, 1, false);
	if (!file_name)
		return (NULL);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		perror("errro open fd\n");
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] > 32 && str[i] < 127)
		i++;
	*start = i;
	if (!dup2(fd, STDOUT_FILENO))
		perror("parssing\n");
	close(fd);
	return (return_str);
}

char	*redirect(char *buff, char *str, int *start)
{
	char	*str_return;

	if (ft_strchr(buff, '>'))
	{
		str_return = redirect_right(str, start);
		*start -= ft_strlen(buff);
		return (str_return);
	}
	else
		return (buff);
}

// lst_argv->fd_output = open(lst_argv->file_output, O_CREAT | O_RDWR | O_APPEND, 0644);