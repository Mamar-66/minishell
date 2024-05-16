/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:25:03 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/16 16:09:05 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	char	*redirect_left_suite(char *str, int *start)
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

char	*redirect_left(char *str, int *start, t_data *lst_data)
{
	char	*str_return;
	char	*file_name;
	int		i_fd[2];

	(void)lst_data;
	i_fd[0] = *start;
	str_return = redirect_left_suite(str, &i_fd[0]);
	file_name = verif_name_file(str + i_fd[0], lst_data);
	if (!file_name)
	{
		free(str_return);
		return (NULL);
	}
	i_fd[1] = open(file_name, O_RDWR);
	if (i_fd[1] == -1)
	{
		printf("minishell: %s: No such file or directory\n", file_name);
		return (NULL);
	}
	// printf("name file = %s\n", file_name);
	// printf("str = %s\n", str_return);
	*start = i_fd[0];
	if (!dup2(STDIN_FILENO, i_fd[1]))
		printf("redirect input\n");
	free(file_name);
	close(i_fd[1]);
	return (str_return);
}
