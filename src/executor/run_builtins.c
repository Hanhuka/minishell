/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:03:55 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/17 17:11:56 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	redirect_in(t_tree *tree)
// {
// 	t_exec e;
// 	int	fd;
	
// 	e.in = count_redirect(tree, e, IN);
// 	while (tree)
// 	{
// 		if (tree->id == IN || tree->id == DOC)
// 		{
// 			i++;
// 			if (tree->id == IN)
// 			{
// 				fd = open(tree->str, O_RDONLY, 0644);
// 				if (fd == -1)
// 					in_error(tree->str);
// 				close(fd);
// 			}
// 			else
// 			{
// 				heredoc_filler(-1, ft_strjoin(tree->str, "\n"), 0);
// 				e->doc = 1;
// 			}
// 		}
// 		tree = tree->left;
// 	}
// }

// void	redirect_out(t_tree *tree)
// {
// 	int	fd;

// 	while (tree)
// 	{
// 		if (tree->id == OUT || tree->id == APD)
// 		{
// 			if (tree->id == OUT)
// 				fd = open(tree->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 			else
// 				fd = open(tree->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 			i++;
// 			if (fd == -1)
// 				in_error(tree->str);
// 			if (i != e->out)
// 				close(fd);
// 			else
// 				dup2(fd, STDOUT_FILENO);
// 		}
// 		tree = tree->left;
// 	}
// }

int	check_builtin2(t_tree *tree, char ***env, char *cmd)
{
	if (cmd && !ft_strncmp(cmd, "exit", ft_strlen("exit") + 1)
		|| !ft_strncmp(cmd, "env", ft_strlen("env") + 1)
		|| !ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1)
		|| !ft_strncmp(cmd, "echo", ft_strlen("echo") + 1)
		|| !ft_strncmp(cmd, "export", ft_strlen("export") + 1)
		|| !ft_strncmp(cmd, "unset", ft_strlen("unset") + 1))
	{
		check_builtin2(tree, env, cmd, fd)
		return (1);
	}
	return (0);
}

int	run_builtin(t_tree *tree, char ***env, char *cmd, int fd)
{
	if (cmd && !ft_strncmp(cmd, "exit", ft_strlen("exit") + 1))
		return (ft_exit(get_args(tree, 0)));
	if (cmd && !ft_strncmp(cmd, "env", ft_strlen("env") + 1))
		return (ft_env(*env, fd));
	if (cmd && !ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1))
		return (ft_pwd(fd));
	if (cmd && !ft_strncmp(cmd, "echo", ft_strlen("echo") + 1))
		return (ft_echo(get_args(tree, 0), fd));
	if (cmd && !ft_strncmp(cmd, "export", ft_strlen("export") + 1))
		return (ft_export(get_args(tree, 0), env, fd));
	if (cmd && !ft_strncmp(cmd, "unset", ft_strlen("unset") + 1))
		return (ft_unset(get_args(tree, 0), env));
	return (0);
}

int	check_builtin(t_tree *tree, char ***env, char *cmd, int pos)
{
	int fd;

	fd = 1;
	// redirect_in(t_tree *tree);
	//add redirections
	if (cmd && !ft_strncmp(cmd, "exit", ft_strlen("exit") + 1))
		return (ft_exit(get_args(tree, pos)));
	if (cmd && !ft_strncmp(cmd, "env", ft_strlen("env") + 1))
		return (ft_env(*env, fd));
	if (cmd && !ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1))
		return (ft_pwd(fd));
	if (cmd && !ft_strncmp(cmd, "echo", ft_strlen("echo") + 1))
		return (ft_echo(get_args(tree, pos), fd));
	if (cmd && !ft_strncmp(cmd, "export", ft_strlen("export") + 1))
		return (ft_export(get_args(tree, pos), env, fd));
	if (cmd && !ft_strncmp(cmd, "unset", ft_strlen("unset") + 1))
		return (ft_unset(get_args(tree, pos), env));
	return (0);
}
