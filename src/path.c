/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:06:21 by marvin            #+#    #+#             */
/*   Updated: 2022/08/02 22:06:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **get_path(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, '/'));
		i++;
	}
	return (NULL);
}

//after the path i need to check every command if its possible to execute
char *test_arg(char **path, t_tree *tree, int cmd)
{
	t_tree *ptr;

	ptr = tree;
	while (ptr)
	{
		if (ptr->id == IN && !open(ptr.str/*isto nao tem o path todo...*/)) //why the fuck nao aparece a func 
			//No input (print Error)
		else if (ptr->id == CMD)
			check_cmd(ptr->str, path);
		if (cmd == 1)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
}

void	check_cmd(char *cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*cmd2

	cmd2 = ft_strjoin("/", cmd);
	free(cmd);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd2)
		if (access(tmp, X_OK))
			return ;
		i++;
		free(tmp);
	}
	//If it reaches here, the command does not exist
}
