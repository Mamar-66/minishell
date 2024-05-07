/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:51:38 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/07 16:26:01 by omfelk           ###   ########.fr       */
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

static	char	*double_redirect_right(char *str, int *start, t_data *lst_data)
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

static	char	*redirect_right(char *str, int *start, t_data *lst_data)
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
		perror("parssing\n");
	free(file_name);
	close(i_fd[1]);
	return (str_return);
}

char	*redirect(char *buff, char *str, int *start, t_data *lst_data)
{
	char	*str_return;
	char	*ptr;

	ptr = ft_strchr(buff, '>');
	if (ptr && *ptr == '>' && *(ptr + 1) == '>' && *(ptr + 2) == '>')
	{
		printf("minishell: syntax token `>'\n");
		return (NULL);
	}
	if (ptr && *ptr == '>' && *(ptr + 1) != '>')
	{
		str_return = redirect_right(str, start, lst_data);
		*start -= ft_strlen(buff);
		return (str_return);
	}
	else if (ptr && *ptr == '>' && *(ptr + 1) == '>')
	{
		str_return = double_redirect_right(str, start, lst_data);
		*start -= ft_strlen(buff);
		return (str_return);
	}
	else
		return (ft_strdup(buff));
}
