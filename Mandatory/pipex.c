/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothin <lothin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:02:50 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/05/11 14:32:28 by lothin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, int p_fd[2], char **envp)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		exit_process(p_fd, errno, argv[1]);
	dup2(filein, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
	close(filein);
	execute(argv[2], envp, p_fd);
}

void	parent_process(char **argv, int p_fd[2], char **envp)
{
	int	fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fileout == -1)
		exit_process(p_fd, errno, argv[4]);
	dup2(p_fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
	close(fileout);
	execute(argv[3], envp, p_fd);
}

int	main(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (argc != 5)
		exit_main(NULL, 0, 1);
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
