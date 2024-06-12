/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_suite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:15:25 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/12 16:39:50 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	printf_error(char *ptr_right, char *ptr_left)
{
	if (ptr_right < ptr_left)
	{
		printf("Minishell: syntax error near unexpected token `<'\n");
		return (false);
	}
	else if (ptr_right > ptr_left)
	{
		printf("Minishell: syntax error near unexpected token `>'\n");
		return (false);
	}
	return (true);
}
