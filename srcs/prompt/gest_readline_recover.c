/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_readline_recover.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:32 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/27 12:55:14 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	gest_readline_recover(char *str)
{
	char	*text;

	if (*str)
	{
		text = recover_word(str, 1);
		if (ft_strncmp(text, "echo", 4) == 0)
			ft_echo(str);
		if (!text)
			printf("%s\n", "null");
		else
			printf("%s\n", text);
		free(text);
	}
	return (false);
}


	// else if (ft_strncmp(text, "cd", 2) == 0)
	// else if (ft_strncmp(text, "pwd", 3) == 0)
	// else if (ft_strncmp(text, "export", 6) == 0)
	// else if (ft_strncmp(text, "unset", 5) == 0)
	// else if (ft_strncmp(text, "env", 3) == 0)
	// else if (ft_strncmp(text, "exit", 4) == 0)