/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:52:18 by znaoui            #+#    #+#             */
/*   Updated: 2022/10/26 12:11:04 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

int		ft_strlen(const char *str);
int		is_empty(char *str);
int		permission_error(char *filename);
int		permission_exec(char *function);
int		openfile(char *filename, int mode);
void	ft_close(int file1, int file2);
void	ft_close_error(int file);
void	close_fd(int pipe_fd[2], int *status);
void	ft_free(char **str);
void	ft_check_error_pipe(int pipe_fd[2]);
void	ft_check_error2(int file1, int file2, char *argv, int pipe_fd[2]);
void	path_exec(char **paths, char **cmds, char *env[], char **pathcmd);
void	ft_check_error(int file1, int file2, char *argv, int pipe_fd[2]);
char	*ft_cut_argv(char *argv);
char	*ft_strjoin(char *str_final, char *str_lign);
char	**ft_split(char *str, char *charset);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
#endif
