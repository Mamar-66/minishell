/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:33:51 by sbarbe            #+#    #+#             */
/*   Updated: 2024/05/13 13:33:52 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_stjoin(char *temp, char *line)
{
	int		i;
	int		j;
	char	*str;

	if (!temp)
	{
		temp = (char *)ft_calloc(1, sizeof(char));
		temp[0] = '\0';
	}
	if (!temp || !line)
		return (NULL);
	str = ft_calloc(sizeof(char), ((ft_strlen(temp) + ft_strlen(line)) + 10));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (temp)
		while (temp[++i] != '\0')
			str[i] = temp[i];
	while (line[j] != '\0')
		str[i++] = line[j++];
	str[ft_strlen(temp) + ft_strlen(line)] = '\0';
	free(temp);
	return (str);
}

void	fre(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

int	v(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == 127)
			i++;
		else
			return (1);
	}
	return (0);
}

void	ft_exportt(char *argv, t_data *env)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (j == 0)
	{
		str = verif(argv + i);
		if (str[0] != '\0')
			ft_unsetbis(str, env);
		if (str[0] == 'a')
			j++;
		free(str);
		i++;
	}
}

char	*veriff(char *a, char *b, size_t i)
{
	int	j;

	j = 0;
	while (a[i] != ' ' && i != ft_strlen(a))
		b[j++] = a[i++];
	return (b);
}
