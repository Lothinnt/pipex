/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothin <lothin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:12:09 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/05/11 17:48:43 by lothin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	initialisation_structure(t_pipex *px, int ac, char **av, char **envp)
{
	px->filein = open(av[1], O_RDONLY);
	if (px->filein == -1)
		exit_process(px->p_fd, errno, av[1]);
	px->fileout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (px->fileout == -1)
		exit_process(px->p_fd, errno, av[ac - 1]);
	px->argc = ac;
	px->argv = av;
	px->envp = envp;
}

pid_t	fork_and_process(int in_fd, int out_fd, char *cmd, t_pipex *px)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		execute(cmd, px->envp, px->p_fd);
	}
	return (pid);
}

int	multi_cmd(t_pipex *px)
{
	int		in_fd;
	int		index;
	pid_t	pid;
	int		status;

	index = 2;
	in_fd = px->filein;
	while (index < px->argc - 2)
	{
		pipe(px->p_fd);
		pid = fork_and_process(in_fd, px->p_fd[1], px->argv[index], px);
		close(px->p_fd[1]);
		close(in_fd);
		in_fd = px->p_fd[0];
		index++;
		waitpid(pid, &status, 0);
	}
	fork_and_process(in_fd, px->fileout, px->argv[index], px);
	close(in_fd);
	close(px->fileout);
	close(px->filein);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
