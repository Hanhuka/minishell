/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:25:48 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/22 15:51:19 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_tree	*tree;
	char	*line;

	(void)ac;
	(void)av;
	tree = NULL;
	(*envi()) = get_env(env);
	while (1)
	{
		line = readline("shell> ");
		add_history(line);
		if (!line)
		{
			printf("\nexit\n");
			exit(0);
		}
		if (!ft_strlen(line))
		{
			free(line);
			continue ;
		}
		parser(line, &tree, 0, 0);
		execute_tree(&tree);
		free_tree(free_tree_utils(&tree));
	}
}
