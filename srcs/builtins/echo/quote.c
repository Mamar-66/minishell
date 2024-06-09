/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:07:57 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/17 20:26:07 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*quote(char *str, t_data *lst_data)
{
	char	*return_str;

	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'' && str[1])
		return_str = ft_strldup(str + 1, 1);
	else if (str[0] == '"' && str[ft_strlen(str) - 1] == '"' && str[1])
		return_str = double_quote(ft_strldup(str + 1, 1), lst_data);
	else
		return_str = NULL;
	if (!return_str && str[0] == '\'')
		printf("error argument simple quote <%s>\n", str);
	else if (!return_str && str[0] == '"')
		printf("error argument double quote <%s>\n", str);
	if (lst_data->here_doc_parssing)
	{
		if (!return_str && str[0] == '\'')
			return (ft_strdup("-1"));
		if (!return_str && str[0] == '"')
			return (ft_strdup("-1"));
	}
	return (return_str);
}
