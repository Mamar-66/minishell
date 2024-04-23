/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:37 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/23 16:45:12 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_pwd()
{
    char    *affiche_pwd;

    affiche_pwd = return_str_pwd();
    printf("%s\n", affiche_pwd);
    free(affiche_pwd);
}
