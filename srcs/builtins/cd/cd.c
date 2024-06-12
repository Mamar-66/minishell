/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:55:56 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/06 12:32:17 by omfelk           ###   ########.fr       */
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
	free(pwd_arg);
	free(oldpwd_arg);
	return ;
}

static void	change_directory(char *path, t_data *env, char **argv)
{
	char	pwd[512];
	char	oldpwd[512];

	if (!path || !getcwd(oldpwd, 512) || chdir(path) || !getcwd(pwd, 512))
	{
		env->status = 1;
		printf("cd: %s: No such file or directory\n", path);
		free(path);
		fre(argv);
		if (env->is_pipe)
			write_in_stdin("", true, env);
		return ;
	}
	fre(argv);
	free(path);
	update_pwd(oldpwd, pwd, env);
	if (env->is_pipe)
		write_in_stdin("", true, env);
}

void	ft_cd(t_data *env, char *st)
{
	char	*path;
	char	**argv;

	st = dollars_parsing_bis(no_space(st), env);
	argv = ft_calloc(sizeof(char *), 3);
	argv = ft_cd_temp(st, argv, 0);
	if (argv[0] && argv[1] && argv[1][0] != 0)
	{
		less_line(argv, env);
		return ;
	}
	if (!argv[0] || !ft_stcmp(argv[0], "~", 2) || !ft_stcmp(argv[0], "--", 3))
	{
		path = ft_getenv(env->env, "HOME");
		if (!path || path[0] == 127)
		{
			cd_ero(argv, env, path);
			return ;
		}
	}
	else
		path = ft_cdd(ft_strdup(argv[0]), argv, env);
	if (!path)
		return ;
	change_directory(path, env, argv);
}
