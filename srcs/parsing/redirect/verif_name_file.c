/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_name_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:59:42 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/11 14:21:52 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	char	*gest_symbole_plus(char *buff, char *str
	, int *start, t_data *lst_data)
{
	char	*buff_return;

	buff_return = NULL;
	(void)buff;
	if (ft_strchr(str, '\''))
		buff_return = quote(str, lst_data);
	else if (ft_strchr(str, '"'))
		buff_return = quote(str, lst_data);
	else if (str)
		buff_return = simple_str(str, str, start, lst_data);
	return (buff_return);
}

static	char	*verif_name_file_suite(char *str, t_data *lst_data)
{
	char	*str_return;

	if (!str)
	{
		free(str);
		return (NULL);
	}
	str_return = gest_symbole_plus(str, str, 0, lst_data);
	if (str_return && ft_strchr(str_return, '/'))
	{
		if (str_return[0] != '/' && str_return[2])
			printf("minishell: %s: No such file or directory\n", str_return);
		else
			printf("minishell: %s: Is a directory\n", str_return);
		free(str);
		free(str_return);
		return (NULL);
	}
	free(str);
	return (str_return);
}

static	void	printf_errror(t_data *lst_data)
{
	if (lst_data->here_doc_parssing)
		printf("minishell: syntax error here_doc end not definited\n");
	else
		printf("minishell: syntax error file name not definited\n");
}

char	*verif_name_file(char *str, t_data *lst_data)
{
	int		i;
	char	*file_name;
	char	c[2];

	i = 0;
	c[0] = 127;
	c[1] = '\0';
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && str[i] > 32 && str[i] < 127)
		file_name = ft_strdup("");
	else
	{
		printf_errror(lst_data);
		return (NULL);
	}
	while (str[i] && str[i] > 32 && str[i] < 127)
	{
		c[0] = str[i++];
		file_name = ft_strjoin(file_name, c);
	}
	file_name = verif_name_file_suite(file_name, lst_data);
	return (file_name);
}
