/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:53:57 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/26 18:11:29 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_process(t_tree *tree, t_exec *e, int *fd)
{
	redirections(tree, e, fd);
	execve(cmd_path(find_command(tree, e->pos), *(e->env)),
		get_args(tree, e->pos), *(e->env));
	exit(127);
}

void	executor(t_tree *tree, t_exec *e, int *fd)
{
	if (pipe(e->p) == -1)
	{
		ft_putstr_fd("Error: couldn't open pipe\n", 2);
		g_status = 1;
		exit(1);
	}
	e->pid = fork();
	if (e->pid < 0)
	{
		ft_putstr_fd("Error: couldn't create a new process\n", 2);
		g_status = 1;
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

t_exec	execute_command(t_tree	*tree, int pos, int count, char ***env)
{
	t_exec		e;
	static int	fd;

	if (!pos)
		fd = 0;
	e.env = env;
	e.count = count;
	e.pos = pos;
	executor(tree, &e, &fd);
	return (e);
}

void	execute_tree(t_tree **tree, char ***env)
{
	t_tree	*ptr;
	int		i;
	int		val2;
	int		count;
	t_exec	e;

	i = 0;
	count = cmd_count(*tree);
	ptr = *tree;
	while (ptr)
	{
		if (!(i == 1 && !(ptr->right)))
			e = execute_command(ptr, i, count, env);
		if (i)
			ptr = ptr->up;
		i++;
	}
	waitpid(e.pid, &val2, 0);
	g_status = WEXITSTATUS(val2);
	i = -1;
	while (++i < count)
		wait(NULL);
	if (e.doc)
		unlink(".heredoc_tmp");
}
