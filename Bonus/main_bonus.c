/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothin <lothin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:02:50 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/05/11 16:33:40 by lothin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int		status;
	t_pipex	px;

	if (argc > 5)
	{
		if (ft_strcmp(argv[1], "here_doc") == 0)
		{
			create_document(argv);
			status = run_pipex(argv, envp);
			unlink("infile");
		}
		else
		{
			initialisation_structure(&px, argc, argv, envp);
			status = multi_cmd(&px);
		}
		return (status);
	}
	exit_main(NULL, 0, 1);
}
