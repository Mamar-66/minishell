/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_suite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:15:25 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/09 23:19:28 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	printf_error(char *ptr_right, char *ptr_left)
{
	char	*tmp;

	tmp = NULL;
	if (ptr_right < ptr_left)
	{
		tmp = recover_word(ptr_right, 2, false);
		if (ft_strchr(tmp, '<') != NULL)
		{
			printf("Minishell: syntax error near unexpected token `<'\n");
			return (free(tmp), false);
		}
	}
	else
	{
		tmp = recover_word(ptr_left, 2, false);
		if (ft_strchr(tmp, '>') != NULL)
		{
			printf("Minishell: syntax error near unexpected token `>'\n");
			return (free(tmp), false);
		}
	}
	if (tmp)
		free(tmp);
	return (true);
}
