/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:22:19 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/07 11:52:18 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	fill_to_pipe(t_tree *tree, t_exec *e)
// {
// 	;
// }

// void	ft_heredoc_fill(t_tree **tree, t_exec *e, int pos)
// {
// 	if (pipe((*tree)->pipe))
// 	{
// 		ft_putstr_fd("Error: couldn't open pipe\n", 2);
// 		g_status = 1;
// 		// return -1;
// 		return ;
// 	}
// 	e->pid = fork();
// 	if (e->pid < 0)
// 	{
// 		ft_putstr_fd("Error: couldn't create a new process\n", 2);
// 		g_status = 1;
// 		exit(1);
// 	}
// 	if (!(e->pid))
// 		fill_to_pipe(tree, e);
// }

// void	ft_heredoc2(t_tree *tree, int pos)
// {
// 	while (tree)
// 	{
// 		if (tree->id == DOC)
// 		{
// 			i++;
// 			ft_heredoc_fill(&tree, e, i);
// 			e->doc = 1;
// 		}
// 		if (!pos)
// 			tree = tree->left;
// 		else
// 			tree = tree->right;
// }

// int	handle_heredoc(t_tree **tree, t_exec *e)
// {
// 	t_tree	*ptr;
// 	int		i;

// 	e->pos = 0;
// 	i = 0;
// 	ptr = *tree;
// 	while (ptr)
// 	{
// 		if (!(i == 1 && !(ptr->right)))
// 			ft_heredoc2(ptr, i);
// 		if (i)
// 			ptr = ptr->up;
// 		i++;
// 	}
// }

void	heredoc_filler_utils(char *str, char *eof, int exit_stat)
{
	ft_putstr_fd("\nshell: warning: here-document delimited ", 1);
	ft_putstr_fd("by end-of-file (wanted `", 1);
	write(1, eof, ft_strlen(eof) - 1);
	ft_putstr_fd("')\n", 1);
	free(eof);
	free(str);
	unlink(".heredoc_tmp");
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
		// ft_putstr_fd("HELLO\n", 2);
		// str = readline("\e[1;95mheredoc> \e[0m");
		str = readline("heredoc> ");
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

	// ft_putstr_fd("HERE!\n", 2);

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
