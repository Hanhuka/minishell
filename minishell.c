/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:25:48 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/26 14:50:51 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_tree	*tree;
	char	*line;
	char	**env2;

	(void)ac;
	(void)av;
	*synt() = 0;
	tree = NULL;
	env2 = get_env(env);
	print_matrix(env2);
	// signal(, def_signals);
	while (1)
	{
		line = readline("shell> ");
		if (line && ft_strlen(line))
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
		parser(line, &tree, 0, env2);
		if (!(*synt()))
			execute_tree(&tree, &env2);
		free_tree(free_tree_utils(&tree));
		*synt() = 0;
	}
}
