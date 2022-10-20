/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:13:45 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/10/18 12:51:10 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	err_handle(char **args)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

int	input_check(char **args, char **env)
{
	int	i;

	if (matrix_size(args) > 2)
	{
		printf("Shell: cd: too many arguments\n");
		return (1);
	}
	i = 0;
	while (env && env[i] != 0)
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (0);
		i++;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	return (1);
}

bool	upd_oldpwd(char ***env, char *path)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		if (!strncmp((*env)[i], "OLDPWD=", 7))
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("OLDPWD=", path);
			return (true);
		}
		i++;
	}
	return (false);
}

int	upd_pwd(char ***env, char *path)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		if (!strncmp((*env)[i], "PWD=", 4))
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("PWD=", path);
			return (1);
		}
		i++;
	}
	return (1);
}

int	ft_cd(char **args, char ***env)
{
	char	path[1025];
	char	*tmp;

	if (input_check(&args[1], *env) == 1)
	{
		free_matrix(args);
		return (1);
	}
	if (getcwd(path, 1025) == NULL)
	{
		free_matrix(args);
		return (1);
	}
	if (matrix_size(args) == 1)
	{
		tmp = treat_dollar2(ft_strdup("$HOME"), *env);
		chdir(tmp);
		free(tmp);
	}
	else if (chdir(args[1]) == -1)
	{
		if (matrix_size(args) > 1)
			err_handle(args);
		free_matrix(args);
		return (1);
	}
	if (!upd_oldpwd(env, path))
	{
		free_matrix(args);
		return (1);
	}
	if (getcwd(path, 1025) == NULL)
	{
		free_matrix(args);
		return (1);
	}
	free_matrix(args);
	return (upd_pwd(env, path));
}
