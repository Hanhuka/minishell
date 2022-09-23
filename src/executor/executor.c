/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:53:57 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/23 16:05:22 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_process(t_tree *tree, t_exec *e, int *fd)
{
	redirections(tree, e, fd);
	execve(cmd_path(find_command(tree, e->pos)),
		get_args(tree, e->pos), *envi());
	exit(127);
}

void	executor(t_tree *tree, t_exec *e, int *fd)
{
	if (pipe(e->p) == -1)
	{
		ft_putstr_fd("Error: couldn't open pipe\n", 2);
		exit(1);
	}
	e->pid = fork();
	if (e->pid < 0)
	{
		ft_putstr_fd("Error: couldn't create a new process\n", 2);
		exit(1);
	}
	if (!(e->pid))
		child_process(tree, e, fd);
	if (e->count != 1)
	{
		if ((*fd) > 0)
			close(*fd);
		close((e->p)[1]);
		*fd = (e->p)[0];
	}
}

void	execute_command(t_tree	*tree, int pos, int count)
{
	t_exec		e;
	static int	fd;

	if (!pos)
		fd = 0;
	e.count = count;
	e.pos = pos;
	executor(tree, &e, &fd);
}

void	execute_tree(t_tree **tree)
{
	t_tree	*ptr;
	int		i;
	int		i2;
	int		count;

	i = 0;
	i2 = -1;
	count = cmd_count(*tree);
	ptr = *tree;
	while (ptr)
	{
		if (!(i == 1 && !(ptr->right)))
			execute_command(ptr, i, count);
		if (i)
			ptr = ptr->up;
		i++;
	}
	while (++i2 < count)
		wait(NULL);
}
