/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export15.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:14:45 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/06 12:14:47 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	trie_print_ajoute(char **temp, char **trier, t_data *env)
{
	temp = trie(trier);
	temp = ajoute(temp);
	print(temp, env);
	fre(trier);
}

void	is_pipe_export(t_data *env, char **trier, char **temp)
{
	if (env->is_pipe)
		write_in_stdin("", true, env);
	fre(trier);
	(void)(temp);
}

void	export_metacarac(char **temp, int i, char *t, t_data *env)
{
	t = ft_strdup(temp[i]);
	if (temp[i][0] == '"' || temp[i][0] == '\'')
		ft_strlcpy(temp[i], temp[i] + 1, ft_strlen(temp[i]) - 1);
	metacarac(temp[i], env, t);
	free(t);
}

void	ft_export_strjoin(t_data *env, char *str)
{
	env->t = ft_stjoin(env->t, " ");
	env->t = ft_strjoin(env->t, str);
}

char	*create_suite(int j, char *temp, int a, char *t)
{
	while (temp[j] && temp[j] == ' ')
	{
		t[a] = temp[j];
		j++;
		a++;
	}
	return (t);
}
