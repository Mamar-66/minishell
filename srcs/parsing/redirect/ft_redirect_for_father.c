/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_for_father.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:02:19 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/11 12:01:53 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*inverse_split_export(char **tab)
{
	int		i;
	char	*temp;
	char	**argv;

	i = 0;
	temp = ft_strdup("");
	while (tab[i])
		i++;
	argv = ft_calloc(sizeof(char *), i + 2);
	i = -1;
	while (tab[++i])
		argv[i] = ft_strjoin(ft_strdup("declare -x "), tab[i]);
	i = 0;
	while (argv[i])
	{
		temp = ft_strjoin(temp, argv[i]);
		if (findn(tab[i]) != 0)
			temp = ft_strjoin(temp, "\"\n");
		else
			temp = ft_strjoin(temp, "\n");
		i++;
	}
	fre(argv);
	return (temp);
}

char	*inverse_split(char **tab)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strdup("");
	while (tab[i])
	{
		temp = ft_strjoin(temp, tab[i]);
		temp = ft_strjoin(temp, "\n");
		i++;
	}
	return (temp);
}

void	write_in_stdin(char *str, bool if_retourne_line,
		t_data *lst_data)
{
	int	pipe_fd[2];

	lst_data->here_doc = true;
	lst_data->here_doc_vrai = true;
	if (pipe(pipe_fd) == -1)
	{
		printf("error pipe heredoc \n");
		return ;
	}
	write(pipe_fd[1], str, ft_strlen(str));
	if (!if_retourne_line)
		write(pipe_fd[1], "\n", ft_strlen(str));
	close(pipe_fd[1]);
	lst_data->fd_here_doc = dup2(pipe_fd[0], STDIN_FILENO);
	if (lst_data->fd_here_doc == -1)
		perror("dup2 :");
	lst_data->is_pipe = false;
	close(pipe_fd[0]);
}
