/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:51:38 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/17 11:42:09 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static suite_redirect()
// {

// }

char	*redirect(char *buff, char *str, int *start, t_data *lst_data)
{
	char	*str_return;
	char	*ptr;

	ptr = ft_strchr(buff, '>');
	// printf("buff= %s\n", buff);
	if (ptr && *ptr == '>' && *(ptr + 1) == '>' && *(ptr + 2) == '>')
	{
		printf("minishell: syntax token `>'\n");
		return (NULL);
	}
	if (ptr && *ptr == '>' && *(ptr + 1) != '>')
	{
		str_return = redirect_right(str, start, lst_data);
		*start -= ft_strlen(buff);
		return (str_return);
	}
	else if (ptr && *ptr == '>' && *(ptr + 1) == '>')
	{
		str_return = double_redirect_right(str, start, lst_data);
		*start -= ft_strlen(buff);
		return (str_return);
	}
	ptr = ft_strchr(buff, '<');
	if (ptr && *ptr == '<' && *(ptr + 1) == '<' && *(ptr + 2) == '<')
	{
		printf("minishell: syntax token `<'\n");
		return (NULL);
	}
	if (ptr && *ptr == '<' && *(ptr + 1) != '<')
	{
		str_return = redirect_left(str, start, lst_data);
		*start -= ft_strlen(buff);
		return (str_return);
	}
	else if (ptr && *ptr == '<' && *(ptr + 1) == '<')
	{
		str_return = double_redirect_left(str, start, lst_data);
		*start -= ft_strlen(buff);
		return (str_return);
	}
	else
		return (ft_strdup(buff));
}
