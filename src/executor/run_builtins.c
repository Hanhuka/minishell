/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:03:55 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/07 19:33:58 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtin(t_tree *tree, char ***env, char *cmd)
{
	if (cmd && !ft_strncmp(cmd, "exit", ft_strlen("exit") + 1))
		return (ft_exit(get_args(tree, 0)));
	if (cmd && !ft_strncmp(cmd, "env", ft_strlen("env") + 1))
		return (ft_env(*env));
	if (cmd && !ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1))
		return (ft_pwd());
	if (cmd && !ft_strncmp(cmd, "echo", ft_strlen("echo") + 1))
		return (ft_echo(get_args(tree, 0)));
	if (cmd && !ft_strncmp(cmd, "export", ft_strlen("export") + 1))
		return (ft_export(get_args(tree, 0), env));
	return (0);
}
