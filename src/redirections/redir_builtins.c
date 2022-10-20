/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:14:12 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/18 15:37:04 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	treat_in(t_tree *tree)
{
	int	fd;

	while (tree)
	{
		if (tree->id == IN || tree->id == DOC)
		{
			if (tree->id == IN)
			{
				fd = open(tree->str, O_RDONLY, 0644);
				if (fd == -1)
					return (built_error(tree->str));
				close(fd);
			}
			else
				heredoc_filler(-1, ft_strjoin(tree->str, "\n"), 0);
		}
		tree = tree->left;
	}
	return (1);
}

int	redirect_in(t_tree *tree)
{
	pid_t	pid;
	int		stat;

	if (!count_redirect(tree, 0, IN))
		return (0);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error: couldn't create a new process\n", 2);
		g_status = 1;
		return (0);
	}
	if (!pid)
		exit(treat_in(tree));
	waitpid(pid, &stat, 0);
	g_status = WEXITSTATUS(stat);
	if (g_status == 255)
		g_status = 1;
	else
		g_status = 0;
	return (g_status);
}
