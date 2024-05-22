/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirect_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:07:14 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/22 09:39:55 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*first_run(char *here_doc_end, t_data *lst_data)
{
	char	*str_return;
	char	buff[2555];

	ft_bzero(buff, 2555);
	read(STDIN_FILENO, buff, 2555);
	str_return = parsing(ft_strdup(buff), lst_data);
	if (ft_strncmp(str_return, "-1", INT_MAX) != 0)
	{
		free(str_return);
		return (NULL);
	}
	if (str_return && !ft_strncmp(str_return, here_doc_end, INT_MAX))
	{
		free(str_return);
		return (NULL);
	}
	if (!str_return)
		str_return = ft_strdup("\n");
	return (str_return);
}

static	char	*continu_here_doc_switch_stdin(t_data *lst_data,
	char *here_doc_end)
{
	char	buff[2555];
	char	*text_here_doc;
	char	*tmp;

	ft_bzero(buff, 2555);
	text_here_doc = first_run(here_doc_end, lst_data);
	if (!text_here_doc)
		return (NULL);
	else
	{
		while (1)
		{
			read(STDIN_FILENO, buff, 2555);
			tmp = parsing(ft_strdup(buff), lst_data);
			if (!tmp)
				tmp = ft_strdup("\n");
			if (!ft_strncmp(tmp, here_doc_end, INT_MAX))
				break ;
			text_here_doc = ft_strjoin(text_here_doc, tmp);
			free(tmp);
		}
	}
	free(tmp);
	return (text_here_doc);
}

bool	here_doc_switch_stdin(t_data *lst_data, char *here_doc_end)
{
	int		pipe_fd[2];
	char	*text_here_doc;

	if (pipe(pipe_fd) == -1)
	{
		printf("error pipe heredoc \n");
		return (false);
	}
	lst_data->here_doc = true;
	text_here_doc = continu_here_doc_switch_stdin(lst_data, here_doc_end);
	if (!text_here_doc)
		return (NULL);
	write(pipe_fd[1], text_here_doc, ft_strlen(text_here_doc));
	close(pipe_fd[1]);
	lst_data->fd_here_doc = dup2(pipe_fd[0], STDIN_FILENO);
	if (lst_data->fd_here_doc == -1)
		perror("dup2 :");
	close(pipe_fd[0]);
	free(text_here_doc);
	return (true);
}

static	char	*redirect_double_left_suite(char *str, int *start)
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
		if (str[i++] == '<')
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

char	*double_redirect_left(char *str, int *start, t_data *lst_data)
{
	char	*str_return;
	char	*text_end_here_doc;
	int		i_fd[2];

	i_fd[0] = *start;
	lst_data->here_doc_parssing = true;
	str_return = redirect_double_left_suite(str, &i_fd[0]);
	text_end_here_doc = verif_name_file(str + ++i_fd[0], lst_data);
	text_end_here_doc = ft_realloc(text_end_here_doc,
			ft_strlen(text_end_here_doc) + 1);
	text_end_here_doc[ft_strlen(text_end_here_doc)] = '\n';
	if (!here_doc_switch_stdin(lst_data, text_end_here_doc))
		return (NULL);
	while (str[i_fd[0]] && str[i_fd[0]] == ' ')
		i_fd[0]++;
	while (str[i_fd[0]] && str[i_fd[0]] > 32 && str[i_fd[0]] < 127)
		i_fd[0]++;
	*start = i_fd[0] + 1;
	free(text_end_here_doc);
	lst_data->here_doc_parssing = false;
	return (str_return);
}
