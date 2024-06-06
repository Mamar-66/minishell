/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:37 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/06 12:31:51 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_data *lst_data)
{
	char	*affiche_pwd;

	affiche_pwd = return_str_pwd();
	if (lst_data->is_pipe)
		write_in_stdin(affiche_pwd, STDOUT_FILENO, lst_data);
	else
		printf("%s\n", affiche_pwd);
	free(affiche_pwd);
}
