/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothin <lothin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:38:53 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/05/11 14:32:28 by lothin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fd(int p_fd[2])
{
	close(p_fd[0]);
	close(p_fd[1]);
}

void	exit_main(int p_fd[2], int need_close, int error_code)
{
	if (need_close)
		close_fd(p_fd);
	if (error_code == 1)
	{
		print_error_in_red("Error: Wrong arguments.\n");
		print_error_in_red("Usage: ./pipex file1 cmd1 cmd2 file2\n");
	}
	else if (error_code == 2)
		print_error_in_red("Error: Pipe creation failed\n");
	else if (error_code == 3)
		print_error_in_red("Error: Fork failed\n");
	exit(1);
}

void	exit_process(int p_fd[2], int err_no, char *argv)
{
	close_fd(p_fd);
	print_error_in_red(argv);
	print_error_in_red(" : ");
	if (err_no == EROFS || err_no == EACCES)
	{
		print_error_in_red("Permission denied\n");
		exit(1);
	}
	else if (err_no == ENOENT)
	{
		print_error_in_red("No such file or directory\n");
		exit(127);
	}
	else
	{
		ft_putstr_fd(strerror(err_no), 2);
		exit(err_no);
	}
}

void	exit_execute(int p_fd[2], int err_no, char *argv, int is_path)
{
	close_fd(p_fd);
	print_error_in_red(argv);
	print_error_in_red(" : ");
	if (err_no == EACCES)
	{
		print_error_in_red("Permission denied\n");
		exit(126);
	}
	else if (err_no == ENOENT && is_path)
	{
		print_error_in_red("No such file or directory\n");
		exit(127);
	}
	else if (err_no == ENOENT)
	{
		print_error_in_red("Command not found\n");
		exit(127);
	}
	else
	{
		ft_putstr_fd(strerror(err_no), 2);
		exit(err_no);
	}
}

void	exit_parsing(char *argv, int p_fd[2], int error_code)
{
	close_fd(p_fd);
	print_error_in_red(argv);
	print_error_in_red(" : ");
	if (error_code == 0)
		print_error_in_red("Command not found\n");
	if (error_code == 1)
		print_error_in_red("No such file or directory\n");
	exit(127);
}
