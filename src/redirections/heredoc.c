/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:22:19 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/17 14:43:48 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_filler_utils(char *str, char *eof, int exit_stat)
{
	ft_putstr_fd("\nshell: warning: here-document delimited ", 1);
	ft_putstr_fd("by end-of-file (wanted `", 1);
	write(1, eof, ft_strlen(eof) - 1);
	ft_putstr_fd("')\n", 1);
	free(eof);
	free(str);
	exit(exit_stat);
}

void	no_heredoc_utils(t_tree *tree, t_exec *e, int i)
{
	int	fd;

	fd = open(tree->str, O_RDONLY, 0644);
	if (fd == -1)
		in_error(tree->str);
	if (i != e->in)
		close(fd);
	else
		dup2(fd, STDIN_FILENO);
}

void	heredoc_filler(int fd, char *eof, int exit_stat)
{
	char	*line;
	char	*str;

	while (1)
	{
		call_sigact(SI_HDOC);
		str = readline("\e[1;95mheredoc> \e[0m");
		if (!str)
			heredoc_filler_utils(str, eof, exit_stat);
		line = ft_strjoin(str, "\n");
		free(str);
		if (line)
		{
			if (!ft_strlen(line))
				break ;
			if (!ft_strncmp(line, eof, ft_strlen(eof)))
				break ;
			if (fd > 0)
				write(fd, line, ft_strlen(line));
			free(line);
		}
	}
	free(eof);
	if (line)
		free(line);
}

void	ft_heredoc(t_tree *tree, t_exec *e, int i)
{
	int		heredoc;

	if (i == e->in)
	{
		heredoc = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (heredoc == -1)
			in_error(tree->str);
		heredoc_filler(heredoc, ft_strjoin(tree->str, "\n"), 0);
		close(heredoc);
		heredoc = open(".heredoc_tmp", O_RDONLY);
		dup2(heredoc, STDIN_FILENO);
	}
	else
		heredoc_filler(-1, ft_strjoin(tree->str, "\n"), 0);
}
