/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothin <lothin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:02:50 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/05/09 02:36:49 by lothin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_wait(pid_t pid2, int *status1, int *status2)
{
	int	finished_pid;

	finished_pid = waitpid(-1, status1, 0);
	while (finished_pid != -1)
	{
		if (finished_pid == pid2)
			*status2 = *status1;
		finished_pid = waitpid(-1, status1, 0);
	}
}

int	evaluate_exit_status(int status2)
{
	int	exit_code;
	int	status_value;

	exit_code = 0;
	status_value = WEXITSTATUS(status2);
	if (status_value == 127)
		exit_code = 127;
	else if (status_value == 126)
		exit_code = 126;
	else if (status_value == 1)
		exit_code = 1;
	else if (status_value == 0)
		exit_code = 0;
	else
		exit_code = status_value;
	return (exit_code);
}
