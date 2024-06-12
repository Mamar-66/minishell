/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirect_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:07:14 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/11 14:24:06 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	if (!text_end_here_doc)
		return (free(str_return), NULL);
	text_end_here_doc = ft_realloc(text_end_here_doc,
			ft_strlen(text_end_here_doc) + 1);
	text_end_here_doc[ft_strlen(text_end_here_doc)] = '\n';
	if (!here_doc_switch_stdin(lst_data, text_end_here_doc))
		return (free(str_return), free(text_end_here_doc), NULL);
	while (str[i_fd[0]] && str[i_fd[0]] == ' ')
		i_fd[0]++;
	while (str[i_fd[0]] && str[i_fd[0]] > 32 && str[i_fd[0]] < 127)
		i_fd[0]++;
	*start = i_fd[0] + 1;
	lst_data->here_doc_parssing = false;
	return (free(text_end_here_doc), str_return);
}
