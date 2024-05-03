/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_name_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:42 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/03 17:45:37 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	char	*gest_symbole_plus(char *buff, char *str
	, int *start, t_data *lst_data)
{
	char	*buff_return;

	(void)buff;
	if (ft_strchr(str,  '\''))
	{
		printf("simple = %s\n", buff);
		buff_return = quote(str, lst_data);
	}
	else if (ft_strchr(str,  '"'))
	{
		printf("double = %s\n", buff);
		buff_return = quote(str, lst_data);
	}
	else if (str)
		buff_return = simple_str(str, str, start, lst_data);
	return (buff_return);
}

static	char	*verif_name_file_suite(char *str, t_data *lst_data)
{
	char	*str_return;

	str_return = gest_symbole_plus(str, str, 0, lst_data);
	printf("str = %s\n", str_return);
	free(str);
	return (str_return);
}

char		*verif_name_file(char *str, t_data *lst_data)
{
	int		i;
	char	*file_name;
	char	c[2];

	i = 0;
	c[0] = 127;
	c[1] = '\0';
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i])
		file_name = ft_strdup("");
	while (str[i] && str[i] > 32 && str[i] < 127)
	{
		c[0] = str[i++];
		file_name = ft_strjoin(file_name, c);
	}
	printf("file name = %s\n", file_name);
	file_name = verif_name_file_suite(file_name, lst_data);
	return (file_name);
}
