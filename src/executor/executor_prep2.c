/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_prep2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:29:14 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/08 11:50:12 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*not_absolute(char *cmd, char **path)
{
	int			i;
	char		*tmp;
	struct stat	statbuf;
	char		*pwd;
	char		*pwd2;

	i = -1;
	if (cmd[0] && cmd[0] == '.')
	{
		pwd = getcwd(NULL, 0);
		pwd2 = ft_strjoin(pwd, "/");
		free(pwd);
		tmp = ft_strjoin(pwd2, cmd);
		lstat(tmp, &statbuf);
		// printf("%s\n%d\n", tmp, S_ISDIR(statbuf.st_mode));
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_putstr_fd("shell: is a directory: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("\n", 2);
			g_status = 126;
			exit(126);
		}
		if (access(tmp, X_OK) >= 0)
		{
			free_matrix(path);
			return (tmp);
		}
		free(tmp);
	}
	if (!path)
	{
		ft_putstr_fd("shell: path is unset\n", 2);
		g_status = 127;
		exit(127);
	}
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		lstat(tmp, &statbuf);
		// printf("%s\n%d\n", tmp, S_ISDIR(statbuf.st_mode));
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_putstr_fd("shell: is a directory: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("\n", 2);
			g_status = 126;
			exit(126);
		}
		if (access(tmp, X_OK) >= 0)
		{
			free_matrix(path);
			return (tmp);
		}
		free(tmp);
	}
	free_matrix(path);
	ft_putstr_fd("shell: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	g_status = 127;
	exit(127);
}

char	*absolute(char *cmd)
{
	DIR	*dirptr;

	dirptr = opendir (cmd);
	if (dirptr)
	{
		closedir(dirptr);
		ft_putstr_fd("shell: permission denied: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		g_status = 126;
		exit(126);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_putstr_fd("shell: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		g_status = 127;
		exit(127);
	}
	return (cmd);
}

char	*cmd_path(char *cmd, char **env)
{
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/')
		return (absolute(cmd));
	else
		return (not_absolute(cmd, get_path(env)));
}

int	nbr_args(t_tree	*tree, int pos)
{
	int	count;

	count = 0;
	while (tree)
	{
		if (tree->id == ARG || tree->id == FLG || tree->id == CMD)
		{
			count++;
		}
		if (!pos)
			tree = tree->left;
		else
			tree = tree->right;
	}
	return (count);
}

char	**get_args(t_tree *tree, int pos)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (nbr_args(tree, pos) + 1));
	i = 0;
	while (tree)
	{
		if (tree->id == ARG || tree->id == FLG || tree->id == CMD)
		{
			args[i++] = ft_strdup(tree->str);
		}
		if (!pos)
			tree = tree->left;
		else
			tree = tree->right;
	}
	args[i] = 0;
	return (args);
}
