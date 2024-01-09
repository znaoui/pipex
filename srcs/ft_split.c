/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znaoui <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:15:03 by znaoui            #+#    #+#             */
/*   Updated: 2022/10/14 14:10:01 by znaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	ft_check_separator(char c, char *charset)
{
	while (*charset != '\0')
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

int	ft_count_word(char *str, char *charset)
{
	int	i;
	int	nb_word;

	i = 0;
	nb_word = 0;
	while (str[i] != '\0')
	{
		while ((str[i] != '\0') && (ft_check_separator(str[i], charset) == 1))
			i++;
		if ((str[i] != '\0') && (ft_check_separator(str[i], charset) == 0))
		{
			nb_word++;
			while ((str[i] != '\0')
				&& (ft_check_separator(str[i], charset) == 0))
				i++;
		}
	}
	return (nb_word);
}

char	*ft_malloc_word(char *str, char *charset)
{
	char	*malloc_dest;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while ((str[len] != '\0') && (ft_check_separator(str[len], charset) == 0))
		len++;
	malloc_dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!malloc_dest)
		return (0);
	while ((str[i] != '\0') && (ft_check_separator(str[i], charset) == 0))
	{
		malloc_dest[i] = str[i];
		i++;
	}
	malloc_dest[i] = '\0';
	return (malloc_dest);
}

char	**ft_split(char *str, char *charset)
{
	char	**split_str;
	int		x;
	int		i;
	int		len;

	i = 0;
	x = 0;
	len = ft_count_word(str, charset);
	split_str = (char **)malloc(sizeof(char *) * (len + 1));
	if (!split_str)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && ft_check_separator(str[i], charset) == 1)
			i++;
		if ((str[i] != '\0') && ft_check_separator(str[i], charset) == 0)
		{
			split_str[x++] = ft_malloc_word(&str[i++], charset);
			while ((str[i] != '\0')
				&& (ft_check_separator(str[i], charset) == 0))
				i++;
		}
	}
	split_str[x] = 0;
	return (split_str);
}
