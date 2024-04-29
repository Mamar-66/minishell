/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:51:38 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/29 17:40:43 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static	void	gest_guillemets(bool *guillemets)
// {

// }

static	void	redirect_right(char *str, int *start)
{
	char	*file_name;
	int		fd;
	int 	i;

	i = *start;
	if (str[i] == '>' && str[i + 1] == '\0')
		i++;
	else
	{
		while (str[i] != '>')
			i++;
		i++;
	}
// printf("text = %s\n", str + *start);
	file_name = recover_word(str + i, 1, false);
// printf("file_name = %s\n", file_name);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (&str[i] != ft_strchr(str + *start, *file_name))
		i++;
	i += ft_strlen(file_name);
	*start = i;
	dup2(fd, STDOUT_FILENO);
}

void	redirect(char *buff, char *str, int *start, t_data *lst_data)
{
	(void)lst_data;

// printf("buff = %s\n", buff);
	if (ft_strchr(buff, '>'))
	{
		redirect_right(str, start);
	}
	// free(buff);
}

// lst_argv->fd_output = open(lst_argv->file_output, O_CREAT | O_RDWR | O_APPEND, 0644);