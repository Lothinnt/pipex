/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:15:17 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/05/12 19:01:08 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "get_next_line.h"

/* Pipex */
void	child_process(char **argv, int p_fd[2], char **envp);
void	parent_process(char **argv, int p_fd[2], char **envp);
void	execute(char *argv, char **envp, int fd_2[2]);

/* Error management */
void	exit_execute(int p_fd[2], int err_no, char *argv, int is_path);
void	exit_main(int p_fd[2], int need_close, int error_code);
void	exit_process(int p_fd[2], int err_no, char *argv);
void	exit_parsing(char *argv, int p_fd[2], int error_code);
void	close_fd(int p_fd[2]);

/* Pipex utils */
char	*find_path(char *cmd, char **envp);
char	*find_executable(char **paths, char *cmd);
void	ft_free(char **array);
char	*ft_strnstr(const char *str, const char *to_find, size_t n);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *str, int fd);
char	*ft_strrchr(const char *s, int c);
char	*is_executable(char *full_path);
int		is_path(char **envp);
void	ft_wait(pid_t pid2, int *status1, int *status2);
int		evaluate_exit_status(int status2);
void	init_status(int *status1, int *status2);
void	print_error_in_red(char *message);

#endif
