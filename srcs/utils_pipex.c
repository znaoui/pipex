/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaktarus <znaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:50:46 by zaktarus          #+#    #+#             */
/*   Updated: 2022/10/25 15:56:38 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int file1, int file2)
{
	if (file1 >= 0)
		close(file1);
	if (file2 >= 0)
		close(file2);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	permission_error(char *filename)
{
	write(2, "pipex: ", 7);
	write(2, "permission denied: ", 19);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
	return (-1);
}

int	openfile(char *filename, int mode)
{
	if (mode == 0)
	{
		if (access(filename, F_OK) == -1)
		{
			write(2, "pipex: ", 8);
			write(2, "no such file or directory: ", 27);
			write(2, filename, ft_strlen(filename));
			write(2, "\n", 1);
			return (-1);
		}
		else if (access(filename, R_OK) == -1)
			return (permission_error(filename));
		else
			return (open(filename, O_RDONLY));
	}
	else
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) == -1)
			return (permission_error(filename));
		else
			return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	}
}
