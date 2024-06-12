/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:07:58 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/12 15:42:06 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// valgrind --leak-check=full --show-leak-kinds=all
//  --suppressions=val.supp -s  ./minishell
int	g_global_numsignal;

// tab_ex[0] = tab_arm_pipe[i] (str_traitement)
// tab_ex[1] = readlin_recover (str)
// tab_ex[2] = dup_tab[i]      (reel)
static	void	pour_norminette(char *readlin_recover, char **tab_arm_pipe
	, char **dup_tab, t_data *lst_data)
{
	char	**tab_ex;

	tab_ex = ft_calloc(sizeof(char *), 4);
	lst_data->exit_f.tab_ex = tab_ex;
	lst_data->exit_f.str_reel = dup_tab;
	if (!tab_ex)
		return ;
	if (!built_or_cmd_for_father(tab_arm_pipe[lst_data->i],
			lst_data, tab_arm_pipe))
	{
		tab_ex[0] = ft_strdup(tab_arm_pipe[lst_data->i]);
		tab_ex[1] = ft_strdup(readlin_recover);
		tab_ex[2] = ft_strdup(dup_tab[lst_data->i]);
		ft_ex(tab_ex, lst_data, tab_arm_pipe, dup_tab);
	}
	my_free_tab(tab_ex);
}

static	void	ft_manager_suite_suite(char **tab_arm_pipe,
	char *readlin_recover, t_data *lst_data)
{
	char	**dup_tab;
	int		i;

	i = -1;
	dup_tab = ft_realloc_tab(tab_arm_pipe, 1, false);
	while (tab_arm_pipe && tab_arm_pipe[++i] && lst_data->status_for_pipe != 2)
	{
		if (!dup_tab[i + 1] && !ft_strchr(dup_tab[i], '>'))
			dup2(lst_data->fd_saved_std_out, STDOUT_FILENO);
		lst_data->pour_toi_simon = 0;
		tab_arm_pipe[i] = parsing(tab_arm_pipe[i], lst_data);
		if (!tab_arm_pipe[i])
		{
			tab_arm_pipe[i] = ft_strdup("");
			break ;
		}
		if ((i > 0 && tab_arm_pipe[i + 1]) && !ft_strchr(dup_tab[i], '>'))
			lst_data->is_pipe = true;
		else if (i > 0 || ft_strchr(dup_tab[i], '>'))
			lst_data->is_pipe = false;
		lst_data->i = i;
		pour_norminette(readlin_recover, tab_arm_pipe, dup_tab, lst_data);
	}
	lst_data->status_for_pipe = 0;
	my_free_tab(dup_tab);
}

static	void	ft_manager_plus(char *readlin_recover, t_data *lst_data)
{
	char	**tab_arm_pipe;

	if (readlin_recover)
	{
		tab_arm_pipe = split_for_ex_pipe(ft_strdup(readlin_recover), lst_data);
		if (!tab_arm_pipe)
			return ;
		if (tab_arm_pipe[0] && tab_arm_pipe[1])
			lst_data->is_pipe = true;
		ft_manager_suite_suite(tab_arm_pipe, readlin_recover, lst_data);
		affiche_in_terminal(lst_data, readlin_recover, tab_arm_pipe);
		free(readlin_recover);
		my_free_tab(tab_arm_pipe);
	}
}

static	bool	ft_manager(t_data *lst_data)
{
	char	*readlin_recover;

	while (true)
	{
		lst_data->here_doc = false;
		lst_data->is_pipe = false;
		dup2(lst_data->fd_saved_std_in, STDIN_FILENO);
		dup2(lst_data->fd_saved_std_out, STDOUT_FILENO);
		readlin_recover = add_signal_plus_return_result_prompt(lst_data);
		if (av_ex(readlin_recover))
			ft_manager_plus(readlin_recover, lst_data);
	}
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data		lst_data;

	(void)argc;
	(void)argv;
	lst_data.status = 0;
	lst_data.status_for_pipe = 0;
	lst_data.here_doc_parssing = false;
	lst_data.mod_lectur_for_read_final = false;
	lst_data.fd_saved_std_out = dup(STDOUT_FILENO);
	lst_data.fd_saved_std_in = dup(STDIN_FILENO);
	lst_data.env = NULL;
	lst_data.lst_pipex.tab_path = NULL;
	lst_data.t = NULL;
	lst_data.tenv = NULL;
	rempli(&lst_data, env);
	ft_manager(&lst_data);
	return (1);
}
