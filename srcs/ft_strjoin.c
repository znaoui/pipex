/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:16:55 by znaoui            #+#    #+#             */
/*   Updated: 2022/10/26 11:42:46 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_error(int file)
{
	close(file);
	exit(EXIT_FAILURE);
}

int	permission_exec(char *function)
{
	if (access(function, F_OK) == -1)
	{
		write(2, "execve: ", 8);
		write(2, "no such file or directory: ", 27);
		write(2, function, ft_strlen(function));
		write(2, "\n", 1);
		return (-1);
	}
	else if (access(function, X_OK) == -1)
	{
		write(2, "execve: ", 8);
		write(2, "no such file or directory: ", 27);
		write(2, function, ft_strlen(function));
		write(2, "\n", 1);
		return (-1);
	}
	else if (access(function, R_OK) == -1)
		return (permission_error(function));
	else
		return (0);
}

void	ft_check_error(int file1, int file2, char *argv, int pipe_fd[2])
{
	if (file1 < 0)
		exit(EXIT_FAILURE);
	if (argv[0] == '\0' || is_empty(argv) == 1)
	{
		write(2, "execve: ", 8);
		write(2, "no such file or directory: ", 27);
		write(2, "\n", 1);
		close(file1);
		close(file2);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		exit(EXIT_FAILURE);
	}
}

void	ft_check_error2(int file1, int file2, char *argv, int pipe_fd[2])
{
	if (file2 < 0)
	{	
		write(2, "pipex: ", 8);
		write(2, "no such file or directory: ", 27);
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	if (argv[0] == '\0' || is_empty(argv) == 1)
	{
		write(2, "execve: ", 8);
		write(2, "no such file or directory: ", 27);
		write(2, "\n", 1);
		close(file1);
		close(file2);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
}

char	*ft_strjoin(char *str_final, char *str_lign)
{
	char	*str_join;
	int		i;
	int		x;

	i = -1;
	x = 0;
	if (!str_final)
	{
		str_final = (char *)malloc(sizeof(char) * 1);
		str_final[0] = '\0';
	}
	if (!str_final || !str_lign)
		return (NULL);
	str_join = (char *)malloc(sizeof(char)
			* (ft_strlen(str_final) + ft_strlen(str_lign) + 1));
	if (!str_join)
		return (NULL);
	while (str_final[++i])
		str_join[i] = str_final[i];
	while (str_lign[x])
		str_join[i++] = str_lign[x++];
	str_join[i] = '\0';
	free(str_final);
	return (str_join);
}
