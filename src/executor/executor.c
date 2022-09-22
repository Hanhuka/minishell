/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:53:57 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/22 16:06:46 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_process(t_tree *tree, t_exec *e, int *fd)
{
	dup2(*fd, STDIN_FILENO);
	close((e->p)[0]);
	if (e->pos == e->count - 1)
		close((e->p)[1]);
	else
		dup2((e->p)[1], STDOUT_FILENO);
	execve(cmd_path(find_command(tree, e->pos)),
		get_args(tree, e->pos), *envi());
	exit(127);
}

void	executor_1(t_tree *tree, t_exec *e)
{
	if (pipe(e->p) == -1)
	{
		printf("error\n");
		exit(1);
	}
	e->pid = fork();
	if (e->pid < 0)
	{
		printf("error\n");
		exit(1);
	}
	if (!(e->pid))
	{
		execve(cmd_path(find_command(tree, e->pos)),
			get_args(tree, e->pos), *envi());
		exit(127);
	}
}

void	executor(t_tree *tree, t_exec *e, int *fd)
{
	if (pipe(e->p) == -1)
	{
		printf("error\n");
		exit(1);
	}
	e->pid = fork();
	if (e->pid < 0)
	{
		printf("error\n");
		exit(1);
	}
	if (!(e->pid))
		child_process(tree, e, fd);
	if ((*fd) > 0)
		close(*fd);
	close((e->p)[1]);
	*fd = (e->p)[0];
}

void	execute_command(t_tree	*tree, int pos, int count)
{
	t_exec		e;
	static int	fd;

	if (!pos)
		fd = 0;
	e.count = count;
	e.pos = pos;
	if (count == 1)
		executor_1(tree, &e);
	else
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
