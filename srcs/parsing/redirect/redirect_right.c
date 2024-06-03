/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:41:35 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/28 14:23:13 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	char	*double_redirect_right_suite(char *str, int *start)
{
	char	*str_return;
	char	c[2];
	int		i;

	i = *start;
	str_return = NULL;
	c[0] = 127;
	c[1] = '\0';
	while (str[i])
	{
		if (str[i++] == '>')
			break ;
		c[0] = str[i - 1];
		if (!str_return)
			str_return = ft_strdup("");
		str_return = ft_strjoin(str_return, c);
	}
	*start = i;
	if (!str_return)
		return (ft_strdup(""));
	return (str_return);
}

char	*double_redirect_right(char *str, int *start, t_data *lst_data)
{
	char	*str_return;
	char	*file_name;
	int		i_fd[2];

	i_fd[0] = *start;
	str_return = double_redirect_right_suite(str, &i_fd[0]);
	file_name = verif_name_file(str + ++i_fd[0], lst_data);
	if (!file_name)
	{
		free(str_return);
		return (NULL);
	}
	i_fd[1] = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (i_fd[1] == -1)
		perror("errro open fd\n");
	while (str[i_fd[0]] && str[i_fd[0]] == ' ')
		i_fd[0]++;
	while (str[i_fd[0]] && str[i_fd[0]] > 32 && str[i_fd[0]] < 127)
		i_fd[0]++;
	*start = i_fd[0];
	if (!dup2(i_fd[1], STDOUT_FILENO))
		perror("parssing\n");
	free(file_name);
	close(i_fd[1]);
	return (str_return);
}

static	char	*redirect_right_suite(char *str, int *start)
{
	char	*str_return;
	char	c[2];
	int		i;

	i = *start;
	str_return = NULL;
	c[0] = 127;
	c[1] = '\0';
	while (str[i])
	{
		if (str[i++] == '>')
			break ;
		c[0] = str[i - 1];
		if (!str_return)
			str_return = ft_strdup("");
		str_return = ft_strjoin(str_return, c);
	}
	*start = i;
	if (!str_return)
		return (ft_strdup(""));
	return (str_return);
}

char	*redirect_right(char *str, int *start, t_data *lst_data)
{
	char	*str_return;
	char	*file_name;
	int		i_fd[2];

	i_fd[0] = *start;
	str_return = redirect_right_suite(str, &i_fd[0]);
	file_name = verif_name_file(str + i_fd[0], lst_data);
	if (!file_name)
	{
		free(str_return);
		return (NULL);
	}
	i_fd[1] = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (i_fd[1] == -1)
		perror("errro open fd\n");
	while (str[i_fd[0]] && str[i_fd[0]] == ' ')
		i_fd[0]++;
	while (str[i_fd[0]] && str[i_fd[0]] > 32 && str[i_fd[0]] < 127)
		i_fd[0]++;
	*start = i_fd[0];
	if (!dup2(i_fd[1], STDOUT_FILENO))
		perror("redirect output simple");
	free(file_name);
	close(i_fd[1]);
	return (str_return);
}
