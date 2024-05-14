/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:07:58 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/14 14:02:39 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// valgrind --leak-check=full --show-leak-kinds=all
//  --suppressions=val.supp -s  ./minishell

static void	affiche_in_terminal(t_data *lst_data)
{
	char	buff[25555];

	ft_bzero(buff, 25555);
	if(lst_data->mod_lectur_for_read_final)
	{
		read(STDIN_FILENO, buff, 25555);
		printf("%s", buff);			
	}
}

static	bool	ft_manager(t_data *lst_data)
{
	char	*readlin_recover;
	char	**tab_arm_pipe;
	int		i;

	while (true)
	{
		i = -1;
		dup2(lst_data->fd_saved_std_in, STDIN_FILENO);
		dup2(lst_data->fd_saved_std_out, STDOUT_FILENO);
		readlin_recover = add_signal_plus_return_result_prompt(lst_data);
		tab_arm_pipe = ft_split(readlin_recover, '|');
		while (tab_arm_pipe && tab_arm_pipe[++i])
		{
			tab_arm_pipe[i] = parsing(tab_arm_pipe[i], lst_data);
			if (!built_or_cmd_for_father(tab_arm_pipe[i], lst_data))
				ft_ex(tab_arm_pipe[i], lst_data, tab_arm_pipe);
		}
		affiche_in_terminal(lst_data);
		my_free_tab(tab_arm_pipe);
	}
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data		lst_data;

	(void)argc;
	(void)argv;
	lst_data.status = -1;
	lst_data.mod_lectur_for_read_final = false;
	lst_data.fd_saved_std_out = dup(STDOUT_FILENO);
	lst_data.fd_saved_std_in = dup(STDIN_FILENO);
	lst_data.env = NULL;
	lst_data.t = NULL;
	lst_data.tenv = NULL;
	rempli(&lst_data, env);
	ft_manager(&lst_data);
	return (1);
}
