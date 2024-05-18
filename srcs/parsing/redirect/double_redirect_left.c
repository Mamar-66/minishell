/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirect_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:07:14 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/18 14:42:52 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


// static void	pipe_close(int *pipe_fd)
// {
// 	close(pipe_fd[0]);
// 	if (!dup2(pipe_fd[1], STDOUT_FILENO))
// 		printf("error dup2 fils here_doc\n");
// 	close(pipe_fd[1]);
// }

static	char	*continu_here_doc_switch_stdin(t_data *lst_data, char *here_doc_end, int *pipe_fd)
{
	(void)pipe_fd;
	char	*buff;
	char	*text_here_doc;

	// pipe_close(pipe_fd);
	text_here_doc = parsing(get_next_line(STDIN_FILENO), lst_data);
	if (!ft_strncmp(text_here_doc, here_doc_end, INT_MAX))
	{
		get_next_line(-1);
		free(text_here_doc);
		return (NULL);
	}
	else
	{
		while (1)
		{
			buff = parsing(get_next_line(STDIN_FILENO), lst_data);
			if (!ft_strncmp(buff, here_doc_end, INT_MAX))
				break ;
			text_here_doc = ft_strjoin(text_here_doc, buff);
			free(buff);
		}
	}
	get_next_line(-1);
	return (free(buff), text_here_doc);
}

bool	here_doc_switch_stdin(t_data *lst_data, char *here_doc_end)
{
	int		pipe_fd[2];
	char	*text_here_doc;
	int 	i;

	if (pipe(pipe_fd) == -1)
	{
		printf("error pipe heredoc \n");
		return (false);
	}
	lst_data->here_doc = true;
	text_here_doc = continu_here_doc_switch_stdin(lst_data, here_doc_end, pipe_fd);
	if (!text_here_doc)
		return (NULL);
	i = write(pipe_fd[1], text_here_doc, ft_strlen(text_here_doc));
	if (i == -1)
	{
		printf("error write");
		return (false);
	}
	close(pipe_fd[1]);
	lst_data->fd_here_doc = dup2(pipe_fd[0], STDIN_FILENO);
	if (lst_data->fd_here_doc == -1)
		perror("dup2 :");
	close(pipe_fd[0]);
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
	str_return = redirect_double_left_suite(str, &i_fd[0]);
	text_end_here_doc = verif_name_file(str + ++i_fd[0], lst_data);
	text_end_here_doc = ft_realloc(text_end_here_doc, ft_strlen(text_end_here_doc) + 1);
	text_end_here_doc[ft_strlen(text_end_here_doc)] = '\n';
	if (!here_doc_switch_stdin(lst_data, text_end_here_doc))
		return (NULL);
	while (str[i_fd[0]] && str[i_fd[0]] == ' ')
		i_fd[0]++;
	while (str[i_fd[0]] && str[i_fd[0]] > 32 && str[i_fd[0]] < 127)
		i_fd[0]++;
	*start = i_fd[0];
	return (str_return);
}
