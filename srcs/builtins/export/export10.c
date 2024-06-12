/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:26:16 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/06 10:26:18 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**notdouble_quote(char **argv)
{
	int	i;
	int	j;
	int	a;
	int	c;

	i = 0;
	j = 0;
	c = 0;
	while (argv[i])
	{
		j = 0;
		c = 0;
		a = 0;
		if (no_quote(argv[i]) == 5)
		{
			argv[i] = flemme_bis(argv, i, j, c);
		}
		else if (no_quote(argv[i]) == 0)
		{
			argv[i] = flemme(argv, i, j, c);
		}
		i++;
	}
	return (argv);
}

char	*replace(char *str, char c)
{
	int		i;
	int		a;
	char	*temp;

	i = 0;
	a = 0;
	temp = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str && str[i + a])
	{
		while (str[i + a] && str[i + a] == c)
			a++;
		if (str[i + a])
			temp[i] = str[i + a];
		if (str[i + a])
			i++;
	}
	temp[i] = '\0';
	free(str);
	return (temp);
}

char	*puthis(char *str, char c)
{
	int		i;
	char	*temp;

	temp = ft_calloc(sizeof(char), ft_strlen(str) + 3);
	i = 0;
	temp[0] = c;
	while (str[i])
	{
		temp[i + 1] = str[i];
		i++;
	}
	temp[i + 1] = c;
	free(str);
	return (temp);
}

char	**replace_quote(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i] && no_quote(argv[i]) == 0)
		{
			argv[i] = replace(argv[i], '"');
			argv[i] = puthis(argv[i], '"');
		}
		if (argv[i] && no_quote(argv[i]) == 5)
		{
			argv[i] = replace(argv[i], '\'');
			argv[i] = puthis(argv[i], '\'');
		}
		i++;
	}
	return (argv);
}

char	*parsing_export(char *nat, t_data *env)
{
	int		z;
	char	**t;
	char	*fin;

	z = 0;
	t = parse_string(nat);
	t = notdouble_quote(t);
	t = replace_quote(t);
	fin = ft_calloc(sizeof(char), 1);
	while (t[z])
	{
		fin = ft_strjoin(fin, t[z]);
		fin = ft_stjoin(fin, " ");
		z++;
	}
	fre(t);
	if (env->dolar == 0)
	{
		free(nat);
	}
	return (fin);
}
