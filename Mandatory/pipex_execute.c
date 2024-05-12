/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:02:50 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/05/12 18:50:38 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*is_executable(char *full_path)
{
	if (full_path && access(full_path, X_OK) == 0)
		return (full_path);
	else
		return (NULL);
}

static void	execute_direct_executable(char *argv, int p_fd[2], char **envp)
{
	char	*cmd[2];

	cmd[0] = argv;
	cmd[1] = NULL;
	if (execve(argv, cmd, envp) == -1)
		exit_execute(p_fd, errno, argv, 0);
}

static void	execute_from_path(char *argv, int p_fd[2], char **envp)
{
	char	*last_slash;
	char	**cmd;
	char	*path;

	last_slash = ft_strrchr(argv, '/');
	cmd = ft_split(last_slash + 1, ' ');
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	path = is_executable(argv);
	if (path == NULL)
		path = find_path(cmd[0], envp);
	if (path == NULL)
	{
		ft_free(cmd);
		exit_execute(p_fd, errno, argv, 1);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free(cmd);
		exit_execute(p_fd, errno, argv, 1);
	}
}

static void	find_and_execute_command(char *av, int p_fd[2], char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_free(cmd);
		exit_execute(p_fd, errno, av, 0);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free(cmd);
		free(path);
		exit_execute(p_fd, errno, av, 0);
	}
	ft_free(cmd);
}

void	execute(char *argv, char **envp, int p_fd[2])
{
	char	*default_envp[2];

	default_envp[0] = "PATH=/bin:/usr/bin:/sbin:/usr/sbin";
	default_envp[1] = NULL;
	if (argv == NULL || argv[0] == ' ')
		exit_parsing(argv, p_fd, 0);
	else if (envp == NULL || envp[0] == NULL)
	{
		if (ft_strchr(argv, '/'))
			execute_from_path(argv, p_fd, default_envp);
		else
			find_and_execute_command(argv, p_fd, default_envp);
	}
	else if (argv[0] == '.' && argv[1] == '/')
		execute_direct_executable(argv, p_fd, envp);
	else if (ft_strchr(argv, '/'))
		execute_from_path(argv, p_fd, envp);
	else
	{
		if (is_path (envp))
			find_and_execute_command(argv, p_fd, envp);
		else
			exit_parsing(argv, p_fd, 1);
	}
}
