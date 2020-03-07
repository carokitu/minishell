/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tirerror1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:47:00 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/15 11:24:20 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	mn_tirerror2(struct stat *in, char *path, int a)
{
	if (a == -1)
	{
		ft_putstr(path);
		ft_putstr(": No such file or directory.\n");
		return ;
	}
	else if (S_ISDIR(in->st_mode) && in)
	{
		ft_putstr(path);
		ft_putstr(": Permission denied.\n");
		return ;
	}
	else
	{
		ft_putstr(path);
		ft_putstr(": Not a directory.\n");
		return ;
	}
}

static int	mn_geti(int i, char *file)
{
	if (i > 0)
		i--;
	while (file[i] && file[i] != '/' && i > 0)
		i--;
	return (i);
}

void		mn_tirerror1(char *path)
{
	int			i;
	char		*file;
	char		*tmp;
	int			a;
	struct stat	*in;

	i = ft_strlen(path) - 1;
	a = 0;
	file = ft_strdup(path);
	if (!(in = (struct stat *)malloc(sizeof(struct stat))))
		return ;
	while (lstat(file, in) == -1 && file[i] &&
			((a = access(file, F_OK)) != 0))
	{
		free(in);
		i = mn_geti(i, file);
		tmp = file;
		file = ft_strsub(tmp, 0, i);
		free(tmp);
		if (!(in = (struct stat *)malloc(sizeof(struct stat))))
			return ;
	}
	mn_tirerror2(in, path, a);
	free(in);
	free(file);
}
