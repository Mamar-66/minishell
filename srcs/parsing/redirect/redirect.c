/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:51:38 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/11 14:37:07 by omfelk           ###   ########.fr       */
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
	while (str[i] && (str[i] == ' ' || str[i] == symb))
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
		g_global_numsignal = 0;
		*start -= ft_strlen(buff);
		return (str_return);
	}
	else
		return (ft_strdup(buff));
}

static	char	*redirect_right_ici(char *buff, char *str,
	int *start, t_data *lst_data)
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

static	bool	ft_verif_quote(char *ptr)
{
	int		i;

	i = 0;
	if (!ptr)
		return (false);
	while (ptr[i])
	{
		if (ptr[i] == '"' || ptr[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

char	*redirect(char *buff, char *str, int *start, t_data *lst_data)
{
	char	*ptr_right;
	char	*ptr_left;

	ptr_right = ft_strchr(str, '>');
	ptr_left = ft_strchr(str, '<');
	if (ft_verif_quote(ptr_right) || ft_verif_quote(ptr_left))
		return (ft_strdup(buff));
	if (ptr_right && ptr_left)
		if (!printf_error(ptr_right, ptr_left))
			return (NULL);
	return (redirect_right_ici(buff, str, start, lst_data));
}
