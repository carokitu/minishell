/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 11:16:48 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/22 14:18:37 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		mn_nbr_arg(char *line, int i)
{
	int	a;
	int	nbr;

	nbr = 1;
	a = i;
	if (!line[a])
		return (1);
	while (line[a] && line[a] < 33)
		a++;
	while (line[a])
	{
		while (line[a] && line[a] < 33)
			a++;
		while (line[a] && line[a] >= 33)
		{
			if (!(line[a + 1]) || (line[a + 1] < 33))
				nbr++;
			a++;
		}
	}
	return (nbr);
}

static void		mn_giveflags(char *line, int i, t_mini *infos)
{
	int a;
	int	e;
	int size;

	size = ft_strlen(line);
	e = 1;
	a = i;
	if (!line)
		return ;
	while (i < size && line[i] != '\0')
	{
		while (line[i] && line[i] < 33)
			i++;
		a = i;
		while (line[i] != '\0' && (line[i + 1] != '\0') && line[i + 1] > 32)
			i++;
		if ((!line[i] && line[i - 1] > 32) || line[i] > 32)
			infos->flags[e++] = ft_strsub(line, a, i - a + 1);
		i++;
	}
	infos->flags[e] = NULL;
}

static int		mn_getflags(int i, char *line, t_mini *infos)
{
	int	a;

	a = mn_nbr_arg(line, i);
	if (!(infos->flags = (char **)malloc(sizeof(char *) * (a + 1))))
		return (1);
	infos->flagson = 1;
	infos->flags[0] = ft_strdup(infos->cmd);
	while (line[i] && line[i] < 33)
		i++;
	mn_giveflags(line, i, infos);
	return (0);
}

int				mn_getarg(t_mini *infos, char *line)
{
	int	i;
	int	a;

	a = 0;
	i = 0;
	if (!line || !line[0])
		return (1);
	while (line[i] && line[i] < 33)
		i++;
	a = i;
	while (line[i] && line[i] > ' ')
		i++;
	if (a == i)
		return (1);
	if ((infos->cmd = ft_strsub(line, a, i - a)) == NULL)
		return (1);
	return (mn_getflags(i, line, infos));
}

int				mn_read(t_mini *infos)
{
	char	*line;
	int		res;
	char	*save;

	save = NULL;
	line = NULL;
	mn_prompt(infos);
	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		res = mn_treat(infos, &line, &save);
		if (infos->flagson == 1)
			mn_freeflags(infos);
		free(line);
		line = NULL;
		if (infos->cmd)
		{
			free(infos->cmd);
			infos->cmd = NULL;
		}
		if (res == -1 || mn_whilesave(infos, &line, &save) == -1)
			return (0);
		mn_prompt(infos);
	}
	return (0);
}
