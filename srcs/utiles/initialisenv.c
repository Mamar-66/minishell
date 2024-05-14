/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:00:04 by sbarbe            #+#    #+#             */
/*   Updated: 2024/05/14 12:31:14 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_env(t_data *lst_data, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[j])
		j++;
	lst_data->env = ft_calloc(sizeof(char *), j + 3);
	while (env[i])
	{
		lst_data->env[i] = ft_strdup(env[i]);
		i++;
	}
}

void	rempli(t_data *ev, char **en)
{
	int		i;
	int		j;
	char	*temp;

	j = 0;
	while (en[j])
		j++;
	ev->tenv = ft_calloc(sizeof(char *), j + 3);
	i = -1;
	while (en[++i])
	{
		ev->tenv[i] = ft_strdup(en[i]);
		if (ft_strncmp(ev->tenv[i], "SHLVL=", 6) == 0)
		{
			j = ft_atoi(ev->tenv[i] + 6);
			free(ev->tenv[i]);
			temp = ft_itoa(j + 1);
			ev->tenv[i] = ft_stoin("SHLVL=", temp);
			free(temp);
		}
	}
	dup_env(ev, ev->tenv);
}
