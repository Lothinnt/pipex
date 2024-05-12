/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:59:56 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/05/12 18:48:50 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(char **argv, int p_fd[2], char **envp)
{
	int	filein;

	filein = open("infile", O_RDONLY);
	if (filein == -1)
		exit_process(p_fd, errno, argv[1]);
	dup2(filein, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
	close(filein);
	execute(argv[3], envp, p_fd);
}

void	parent_process(char **argv, int p_fd[2], char **envp)
{
	int	fileout;

	fileout = open(argv[5], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fileout == -1)
		exit_process(p_fd, errno, argv[5]);
	dup2(p_fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
	close(fileout);
	execute(argv[4], envp, p_fd);
}

int	run_pipex(char **argv, char **envp)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	init_status(&status1, &status2);
	if (pipe(p_fd) == -1)
		exit_main(NULL, 0, 2);
	pid1 = fork();
	if (pid1 == -1)
		exit_main(p_fd, 1, 3);
	if (pid1 == 0)
		child_process(argv, p_fd, envp);
	pid2 = fork();
	if (pid2 == -1)
		exit_main(p_fd, 1, 3);
	if (pid2 == 0)
		parent_process(argv, p_fd, envp);
	close_fd(p_fd);
	ft_wait(pid2, &status1, &status2);
	return (evaluate_exit_status(status2));
}
