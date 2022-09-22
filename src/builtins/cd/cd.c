/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:13:45 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/09/22 17:03:10 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include "../builtins.h"

void	err_handle(char **args)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

int	input_check(char **args, char **env bool input)
{
	int	i;

	if (args[1] != 0)
	{
		*input = true;
		return (1);
	}
	*input = false;
	i = 0;
	while (env && env[i] != 0)
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (1);
		i++;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	return (0);
}

static int	upd_pwd(int fd, char ***env, char **args, bool input)
{
	int	i;
}

int	ft_cd(char **args, int fd, char ***env)
{
	char	path[1025];
	bool	input;

	if (fd > 2)
		close (fd);
	if (input_check(&args[1], *env, &input) == 0)
		return (1);
	if (getcwd(pwd, 1025) == NULL)
	{
		werror("cd");
		return (errno);
	}
	if (chdir(args[1]) == -1)
	{
		err_handle(args);
		return (errno);
	}
	if (chage_pwd_vars("OLDPWD=", pwd, env, buf))
		return (errno);
	return (upd_pwd(fd, env, &args[1], input));
}
