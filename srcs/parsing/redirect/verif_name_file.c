/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_name_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:42 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/03 12:02:57 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char		*verif_name_file(char *str)
{
	// char	*str_return;

	if (!str)
	{
		printf("bash: syntax error file name not defined\n");
		return (NULL);
	}
	if (str[0] == '\'')
		return (str);
	printf("str = %s\n", recover_word(str, 1, true));
	return (str);
}
