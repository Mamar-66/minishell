/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirect_left_suite.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:10:59 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/11 15:08:13 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	bool	verif_read(char *buff, char *here_doc_end)
{
	if (g_global_numsignal == 130 && !buff)
		return (false);
	else if (!buff)
	{
		printf("\x1b[31mMinishell: warning: here-document");
		printf("at line 1 delimited ");
		here_doc_end[ft_strlen(here_doc_end) - 1] = '\0';
		printf("by end-of-file (wanted \x1b[0m");
		printf("\033[38;5;208m`%s'\033[0m\x1b[31m)\x1b[0m\n", here_doc_end);
		return (false);
	}
	return (true);
}

static char	*first_run(char *here_doc_end, t_data *lst_data)
{
	char	*buff;
	char	*str_return;

	buff = readline("here_doc > ");
	if (!verif_read(buff, here_doc_end))
		return (free(buff), NULL);
	str_return = parsing(ft_strdup(buff), lst_data);
	if (str_return && !ft_strncmp(str_return, "-1", INT_MAX))
	{
		free(str_return);
		return (free(buff), NULL);
	}
	if (str_return && !ft_strncmp(str_return, here_doc_end, INT_MAX))
	{
		free(str_return);
		return (free(buff), NULL);
	}
	if (!str_return)
		str_return = ft_strdup("\n");
	return (free(buff), str_return);
}

static	char	*run(char *text, char *here_doc_end, t_data *lst_data)
{
	char	*text_here_doc;
	char	*tmp;

	text_here_doc = ft_strdup(text);
	free(text);
	while (1 && text_here_doc)
	{
		tmp = readline("here_doc > ");
		if (!verif_read(tmp, here_doc_end))
			break ;
		tmp = parsing(ft_strdup(tmp), lst_data);
		if (!tmp)
			tmp = ft_strdup("\n");
		if (text_here_doc && !ft_strncmp(text_here_doc, "-1", INT_MAX))
			return (free(text_here_doc), free(tmp), NULL);
		if (!ft_strncmp(tmp, here_doc_end, INT_MAX))
			break ;
		text_here_doc = ft_strjoin(text_here_doc, tmp);
		free(tmp);
	}
	if (tmp)
		free(tmp);
	return (text_here_doc);
}

static	char	*continu_here_doc_switch_stdin(t_data *lst_data,
	char *here_doc_end)
{
	char	*text_here_doc;

	g_global_numsignal = -10;
	dup2(lst_data->fd_saved_std_in, STDIN_FILENO);
	text_here_doc = first_run(here_doc_end, lst_data);
	if (!text_here_doc)
		return (ft_strdup(""));
	else
		text_here_doc = run(text_here_doc, here_doc_end, lst_data);
	return (text_here_doc);
}

bool	here_doc_switch_stdin(t_data *lst_data, char *here_doc_end)
{
	int		pipe_fd[2];
	char	*text_here_doc;
	bool	wr;

	wr = true;
	if (pipe(pipe_fd) == -1)
	{
		printf("error pipe heredoc \n");
		return (false);
	}
	lst_data->here_doc = true;
	lst_data->here_doc_vrai = true;
	text_here_doc = continu_here_doc_switch_stdin(lst_data, here_doc_end);
	if (g_global_numsignal != 130)
		write(pipe_fd[1], text_here_doc, ft_strlen(text_here_doc));
	else
		wr = false;
	lst_data->fd_here_doc = dup2(pipe_fd[0], STDIN_FILENO);
	if (lst_data->fd_here_doc == -1)
		perror("dup2 :");
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	free(text_here_doc);
	return (wr);
}
