/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:15:17 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/05/12 19:01:11 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../includes/ft_printf.h"
# include "../includes/get_next_line.h"

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	int		p_fd[2];
	int		filein;
	int		fileout;
	int		argc;
}	t_pipex;

/* Pipex Bonus : Here_doc */
void	create_document(char **argv);
int		run_pipex(char **argv, char **envp);
void	child_process(char **argv, int p_fd[2], char **envp);
void	parent_process(char **argv, int p_fd[2], char **envp);
void	execute(char *argv, char **envp, int fd_2[2]);

/* Pipex Bonus : Multi_cmd */
int		multi_cmd(t_pipex *px);
pid_t	fork_and_process(int in_fd, int out_fd, char *cmd, t_pipex *px);
void	initialisation_structure(t_pipex *px, int ac, char **av, char **envp);

/* Error management */
void	exit_execute(int p_fd[2], int err_no, char *argv, int is_path);
void	exit_main(int p_fd[2], int need_close, int error_code);
void	exit_process(int p_fd[2], int err_no, char *argv);
void	exit_parsing(char *argv, int p_fd[2], int error_code);
void	close_fd(int p_fd[2]);
void	print_error_in_red(char *message);

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

/* Bonus tools */
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *first, const char *second, size_t length);

#endif
