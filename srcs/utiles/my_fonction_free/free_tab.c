/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:38:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/22 10:01:08 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	freeverithing(t_data *env)
{
	if (env->lst_pipex.tab_path)
		fre(env->lst_pipex.tab_path);
	if (env->tenv)
		fre(env->tenv);
	if (env->t)
		free(env->t);
	if (env->env)
		fre(env->env);
}

void	my_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_free_que_argv(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
}
