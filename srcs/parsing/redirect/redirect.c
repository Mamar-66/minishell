/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:51:38 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/21 15:41:21 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	bool	cmp_symb(char *str, char symb)
{
	int		i;
	int		j;
	bool	space;

	i = 0;
	j = 0;
	space = false;
	while (str[i] && str[i] != symb)
		i++;
	while(str[i] && (str[i] == ' ' || str[i] == symb))
	{
		if (str[i] == symb && space)
			return (false);
		else if (str[i] == symb)
			j++;
		if (str[i] == ' ')
			space = true;
		i++;
	}
	if (j > 2)
		return (false);
	return (true);
}

static	char	*suite_redirect(char *buff, char *str,
	int *start, t_data *lst_data)
{
	char	*str_return;
	char	*ptr;

	ptr = ft_strchr(buff, '<');
	if (ptr && !cmp_symb(str + *start, '<'))
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

char	*redirect(char *buff, char *str, int *start, t_data *lst_data)
{
	char	*str_return;
	char	*ptr;

	ptr = ft_strchr(buff, '>');
	if (ptr && !cmp_symb(str + *start, '>'))
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
	return (suite_redirect(buff, str, start, lst_data));
}
