/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:55:56 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/26 15:56:05 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_stoin(char *temp, char *line)
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
	str = ft_calloc(sizeof(char), ((ft_strlen(temp) + ft_strlen(line)) + 3));
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
	return (str);
}

void	change(char *pwd, char *oldpwd, t_data *env)
{
	int	i;

	i = 0;
	while (env->tenv[i])
	{
		if (ft_strncmp(env->tenv[i], pwd, 5) == 0)
		{
			free(env->tenv[i]);
			env->tenv[i] = ft_strdup(pwd);
		}
		else if (ft_strncmp(env->tenv[i], oldpwd, 8) == 0)
		{
			free(env->tenv[i]);
			env->tenv[i] = ft_strdup(oldpwd);
		}
		i++;
	}
}

static void	update_pwd(char *oldpwd, char *pwd, t_data *env)
{
	char	*pwd_arg;
	char	*oldpwd_arg;

	if (!oldpwd || !pwd)
		return ;
	pwd_arg = ft_stoin("PWD=", pwd);
	if (!pwd_arg)
		return ;
	oldpwd_arg = ft_stoin("OLDPWD=", oldpwd);
	if (!oldpwd_arg)
	{
		free(pwd_arg);
		return ;
	}
	change(pwd_arg, oldpwd_arg, env);
	if (env->env)
		changes(pwd_arg, oldpwd_arg, env);
	return ;
}

static void	change_directory(const char *path, t_data *env, char **argv)
{
	char	pwd[512];
	char	oldpwd[512];

	if (!path || !getcwd(oldpwd, 512) || chdir(path) || !getcwd(pwd, 512))
	{
		env->status = 1;
		printf("No file or directory\n");
		return ;
	}
	fre(argv);
	update_pwd(oldpwd, pwd, env);
}

void	ft_cd(char *str, t_data *env)
{
	char	*path;
	char	**argv;

	argv = ft_split(str, ' ');
	if (argv[2])
	{
		fre(argv);
		env->status = 1;
		printf("mishelle: cd: too many arguments\n");
		return ;
	}
	if (!argv[1] || !ft_strncmp(argv[1], "~", 2))
	{
		path = getenv("HOME");
		if (!path)
		{
			fre(argv);
			env->status = 1;
			printf("mishelle: cd: HOME not set\n");
			return ;
		}
	}
	else
		path = ft_cdd(argv, env);
	change_directory(path, env, argv);
}
