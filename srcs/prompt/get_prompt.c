/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:45:36 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/22 10:45:49 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_result_prompt(void)
{
	char	*prompt;
	char	*result_prompt;

	prompt = return_pwd();
	result_prompt = readline(prompt);
	free(prompt);
	return (result_prompt);
}
