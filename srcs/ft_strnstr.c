/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:17:52 by znaoui            #+#    #+#             */
/*   Updated: 2022/10/26 12:11:40 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_error_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"));
}

void	close_fd(int pipe_fd[2], int *status)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(status);
	wait(status);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

void	path_exec(char **paths, char **cmds, char *env[], char **pathcmd)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		*pathcmd = ft_strjoin(paths[i], "/");
		*pathcmd = ft_strjoin(*pathcmd, cmds[0]);
		execve(*pathcmd, cmds, env);
		free(*pathcmd);
		i++;
	}	
}

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	y;
	size_t	rep;

	i = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[i] != '\0' && i < len)
	{
		rep = i;
		if (s1[i] == s2[0])
		{
			y = 0;
			while (s1[rep] && s2[y] && s1[rep] == s2[y] && rep < len)
			{
				rep++;
				y++;
			}
			if (s2[y] == '\0')
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (NULL);
}
