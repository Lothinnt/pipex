/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothin <lothin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:02:50 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/04/28 23:24:45 by lothin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_status(int *status1, int *status2)
{
	*status1 = 0;
	*status2 = 0;
}

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occurrence = NULL;

	while (*s != '\0')
	{
		if (*s == c)
			last_occurrence = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *)last_occurrence);
}

int	is_path(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (0);
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			return (1);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void	print_error_in_red(char *message)
{
	char	*red_start;
	char	*red_end;

	red_start = "\033[31m";
	red_end = "\033[0m";
	ft_putstr_fd(red_start, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(red_end, 2);
}
