/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:25:03 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/06 17:19:25 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	int	saut(char *str, int i_fd)
{
	int	int_return;

	int_return = i_fd;
	if (ft_strncmp(str, "echo", 4) == 0 || ft_strncmp(str, "export", 6) == 0
		|| ft_strncmp(str, "cd", 2) == 0 || ft_strncmp(str, "ls", 2) == 0)
	{
		while (str[int_return] && str[int_return] == ' ')
			int_return++;
		while (str[int_return] && str[int_return] > 32 && str[int_return] < 127)
			int_return++;
		int_return++;
	}
	return (int_return);
}

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

	i_fd[0] = *start;
	str_return = redirect_left_suite(str, &i_fd[0]);
	file_name = verif_name_file(str + i_fd[0], lst_data);
	if (!file_name)
		return (free(str_return), NULL);
	i_fd[1] = open(file_name, O_RDWR);
	if (i_fd[1] == -1)
	{
		printf("minishell: %s: No such file or directory\n", file_name);
		if (str_return)
			free(str_return);
		return (free(file_name), NULL);
	}
	*start = saut(str, i_fd[0]);
	if (!dup2(STDIN_FILENO, i_fd[1]))
		printf("redirect input\n");
	free(file_name);
	close(i_fd[1]);
	return (str_return);
}
