/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:33:02 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/23 14:08:53 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			mn_error_cd2(char *path, struct stat *in)
{
	if (S_ISDIR(in->st_mode))
	{
		ft_putstr("cd: permission denied: ");
		ft_putstr(path);
		ft_putchar('\n');
	}
	else
	{
		ft_putstr("cd: not a directory: ");
		ft_putstr(path);
		ft_putchar('\n');
	}
	return ;
}

static int		mn_error_cd1bis(struct stat *in, char *file, char *path)
{
	if (lstat(file, in) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(path);
		ft_putchar('\n');
		free(in);
		free(file);
		file = NULL;
		return (1);
	}
	else
	{
		if (S_ISDIR(in->st_mode))
		{
			free(in);
			return (0);
		}
		ft_putstr("cd: not a directory: ");
		ft_putstr(path);
		ft_putchar('\n');
		free(file);
		file = NULL;
		free(in);
		return (1);
	}
}

void			mn_error_cd1(char *path)
{
	int			i;
	char		*file;
	struct stat	*in;

	i = 0;
	file = NULL;
	while (path[i])
	{
		if (path[i] == '/')
		{
			if (file != NULL)
				free(file);
			if (!(in = (struct stat *)malloc(sizeof(struct stat))))
				return ;
			file = ft_strsub(path, 0, i);
			if (mn_error_cd1bis(in, file, path) == 1)
				return ;
		}
		i++;
	}
	ft_putstr("cd: no such file or directory: ");
	ft_putstr(path);
	ft_putchar('\n');
	free(file);
}
