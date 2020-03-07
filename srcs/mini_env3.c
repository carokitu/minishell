/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:31:01 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/09 12:27:31 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		mn_getnewenv(t_mini *infos, int a)
{
	char	**tmp;
	int		i;
	int		b;

	tmp = infos->tmp_env;
	if (a == -1 || infos->tmp_env == NULL || infos->tmp_env[0] == NULL)
		return ;
	i = 0;
	while (tmp[i])
		i++;
	if (!(infos->tmp_env = (char **)malloc(sizeof(char *) * (i + 1))))
		return ;
	i = -1;
	b = 0;
	while (tmp[++i])
	{
		if (i != a)
			infos->tmp_env[b++] = ft_strdup(tmp[i]);
	}
	infos->tmp_env[b] = NULL;
	mn_freesave(tmp, 1);
}

char		**mn_dupstr(char **str)
{
	char	**new;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (!(new = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = ft_strdup(str[i]);
	new[i] = NULL;
	return (new);
}

int			mn_checkenv1(char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'u' && str[i] != 'i')
		{
			mn_enverror(str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int			mn_enverror(char arg)
{
	ft_putstr("env: illegal option -- ");
	ft_putchar(arg);
	ft_putstr("\nusage: env [-i]");
	ft_putstr("[-u name]\n");
	ft_putstr("\t [name=value ...] [utility [argument ...]]\n");
	return (2);
}
