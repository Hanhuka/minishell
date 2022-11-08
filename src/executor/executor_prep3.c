/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_prep3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:16:41 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/08 16:18:34 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	command_error(char *str, char *cmd, int stat)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	g_status = stat;
	exit(stat);
}

void	no_path(char **path)
{
	if (!path)
	{
		ft_putstr_fd("shell: path is unset\n", 2);
		g_status = 127;
		exit(127);
	}
}

int	check_path(char *cmd, char *tmp, char **path)
{
	struct stat	statbuf;

	lstat(tmp, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
		command_error("shell: is a directory: ", cmd, 126);
	if (access(tmp, X_OK) >= 0)
	{
		free_matrix(path);
		return (1);
	}
	free(tmp);
	return (0);
}
