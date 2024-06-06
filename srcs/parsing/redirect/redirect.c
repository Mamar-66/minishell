/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:51:38 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/06 14:45:54 by omfelk           ###   ########.fr       */
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

char	*redirect(char *buff, char *str, int *start, t_data *lst_data)
{
	char	*ptr_right;
	char	*ptr_left;
	char	*tmp;

	ptr_right = ft_strchr(str, '>');
	ptr_left = ft_strchr(str, '<');
	tmp = NULL;
	if (ptr_right && ptr_left)
	{
		if (ptr_right < ptr_left)
		{
			tmp = recover_word(ptr_right, 2, false);
			if (ft_strchr(tmp, '<') != NULL)
				printf("Minishell: syntax error near unexpected token `<'\n");
			return (free(tmp), NULL);
		}
		else
		{
			tmp = recover_word(ptr_left, 2, false);
			if (ft_strchr(tmp, '>') != NULL)
				printf("Minishell: syntax error near unexpected token `>'\n");
			return (free(tmp), NULL);
		}
	}
	return (free(tmp), redirect_right_ici(buff, str, start, lst_data));
}
