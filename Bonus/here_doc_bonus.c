/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothin <lothin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:04:20 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/05/08 19:24:21 by lothin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (first[i] != second[i] || first[i] == '\0' || second[i] == '\0')
		{
			return (((unsigned char)first[i]) -((unsigned char)second[i]));
		}
		i++;
	}
	return (0);
}

void	create_document(char **argv)
{
	char	*input;
	int		fd;

	fd = open("infile", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (1)
	{
		input = get_next_line(STDIN_FILENO, 0);
		if (!input)
		{
			printf("Fail to read input");
			exit(errno);
		}
		if ((ft_strncmp(input, argv[2], ft_strlen(argv[2])) == 0)
			&& (strlen(input) - 1) == strlen(argv[2]))
		{
			free(input);
			get_next_line(STDIN_FILENO, 1);
			close(fd);
			return ;
		}
		ft_putstr_fd(input, fd);
		free (input);
	}
	close (fd);
}
