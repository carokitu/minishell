/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_separg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 10:10:12 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/18 17:03:43 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	mn_checkline(char **line, char **save)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while ((*line)[i] && (*line)[i] != ';')
		i++;
	if (!((*line)[i]))
		return ;
	tmp = ft_strdup(*line);
	free(*line);
	*line = NULL;
	*line = ft_strsub(tmp, 0, i);
	*save = ft_strsub(tmp, i + 1, ft_strlen(tmp) - i);
	free(tmp);
	tmp = NULL;
}

static void	mn_checksave(char **line, char **save)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while ((*save)[i] && (*save)[i] != ';')
		i++;
	if (!((*save)[i]))
	{
		if (*save[0])
			*line = ft_strdup(*save);
		else
			*line = NULL;
		free(*save);
		*save = NULL;
		return ;
	}
	tmp = ft_strdup(*save);
	free(*save);
	*save = NULL;
	*line = ft_strsub(tmp, 0, i);
	if (tmp[i + 1])
		*save = ft_strsub(tmp, i + 1, ft_strlen(tmp) - i);
	free(tmp);
	tmp = NULL;
}

void		mn_checksep(char **line, char **save)
{
	int	i;

	i = 0;
	if (!(*line) && (!(*save) || ft_strlen(*save) == 0))
	{
		if (*save && ft_strlen(*save) == 0)
		{
			free(*save);
			*save = NULL;
		}
		return ;
	}
	if (*line && !(*save))
		mn_checkline(line, save);
	else if (*save)
		mn_checksave(line, save);
}

int			mn_whilesave(t_mini *infos, char **line, char **save)
{
	while (*save)
	{
		mn_treat(infos, line, save);
		if (infos->flagson == 1)
			mn_freeflags(infos);
		free(*line);
		*line = NULL;
		if (infos->cmd)
		{
			free(infos->cmd);
			infos->cmd = NULL;
		}
	}
	if (infos->exit == 1)
		return (-1);
	return (0);
}
