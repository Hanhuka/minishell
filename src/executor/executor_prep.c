/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_prep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:26:20 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/22 16:06:39 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmd_count(t_tree *tree)
{
	int	i;

	i = 0;
	while (tree)
	{
		if (!i && tree->right)
			i++;
		i++;
		tree = tree->up;
	}
	return (i);
}

char	*find_command(t_tree	*tree, int pos)
{
	if (!pos)
		while (tree && tree->id != CMD)
			tree = tree->left;
	else
		while (tree && tree->id != CMD)
			tree = tree->right;
	return (tree->str);
}

char	**get_path(char **env)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path = ft_split(env[i] + 5, ':');
			i = 0;
			while (path[i])
			{
				tmp = ft_strdup(path[i]);
				free(path[i]);
				path[i] = ft_strjoin(tmp, "/");
				free(tmp);
				i++;
			}
			return (path);
		}
		i++;
	}
	return (NULL);
}
