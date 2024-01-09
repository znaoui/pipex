/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:51:42 by znaoui            #+#    #+#             */
/*   Updated: 2022/10/26 12:12:03 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char *env[])
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i], "=:");
			return (paths);
		}
		i++;
	}
	return (NULL);
}

int	treat_child_one(int file1, int pipe_fd[2], char *argv, char *env[])
{
	char		*pathcmd;
	char		**paths;
	char		**cmds;

	close(pipe_fd[0]);
	if (dup2(file1, 0) == -1 || dup2(pipe_fd[1], 1) == -1)
		return (perror("dup2"), -1);
	paths = get_path(env);
	cmds = ft_split(argv, " ");
	if (paths)
		path_exec(paths, cmds, env, &pathcmd);
	if (permission_exec(cmds[0]) == 0)
		execve(cmds[0], cmds, env);
	ft_free(cmds);
	free(paths);
	close(file1);
	close(pipe_fd[1]);
	return (-1);
}

int	treat_child_two(int file2, int pipe_fd[2], char *argv, char *env[])
{
	char	*pathcmd;
	char	**paths;
	char	**cmds;

	close(pipe_fd[1]);
	if (dup2(file2, 1) == -1 || dup2(pipe_fd[0], 0) == -1)
		return (perror("dup2"), -1);
	paths = get_path(env);
	cmds = ft_split(argv, " ");
	if (paths)
		path_exec(paths, cmds, env, &pathcmd);
	if (permission_exec(cmds[0]) == 0)
		execve(cmds[0], cmds, env);
	ft_free(cmds);
	free(paths);
	close(file2);
	close(pipe_fd[0]);
	return (-1);
}

void	pipex(int file1, int file2, char *argv[], char *env[])
{
	pid_t		child1;
	pid_t		child2;
	int			pipe_fd[2];
	int			status;

	ft_check_error_pipe(pipe_fd);
	child1 = fork();
	if (child1 == -1)
		return (perror("fork"));
	if (child1 == 0)
	{
		ft_check_error(file1, file2, argv[2], pipe_fd);
		if (treat_child_one(file1, pipe_fd, argv[2], env) == -1)
			ft_close_error(file2);
	}
	child2 = fork();
	if (child2 == -1)
		return (perror("fork"));
	if (child2 == 0)
	{
		ft_check_error2(file1, file2, argv[3], pipe_fd);
		if (treat_child_two(file2, pipe_fd, argv[3], env) == -1)
			ft_close_error(file1);
	}
	close_fd(pipe_fd, &status);
}

int	main(int argc, char *argv[], char *env[])
{
	int	file1;
	int	file2;

	if (argc != 5)
		return (write(2, "Invalid number of arguments.\n", 29));
	file1 = openfile(argv[1], 0);
	file2 = openfile(argv[4], 1);
	if (file1 < 0)
	{
		ft_close(file1, file2);
		exit(EXIT_FAILURE);
	}
	if (file2 < 0)
	{
		write(2, "execve: ", 8);
		write(2, "no such file or directory: ", 27);
		write(2, argv[4], ft_strlen(argv[4]));
		write(2, "\n", 1);
		ft_close(file1, file2);
		exit(EXIT_FAILURE);
	}
	pipex(file1, file2, argv, env);
	ft_close(file1, file2);
	return (0);
}
