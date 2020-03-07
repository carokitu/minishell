/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_checkdolls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:45:11 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/22 14:19:10 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		mn_freethree(char **un, char **deux, char **trois)
{
	free(*un);
	free(*deux);
	free(*trois);
}

char		*mn_printdolls(char **un, char **deux, char **trois, t_mini *infos)
{
	mn_freethree(un, deux, trois);
	infos->skipenv = 1;
	return (ft_strdup("error"));
}

char		*mn_dolls2(char **flag, int i, int start, char **ctn)
{
	char	*new;
	char	*env;

	env = ft_strsub(*flag, 0, start);
	if (env != NULL)
		new = ft_strjoin(env, *ctn);
	else
		new = ft_strdup(*ctn);
	free(env);
	free(*ctn);
	*ctn = ft_strsub(*flag, i, ft_strlen(*flag) - i);
	env = ft_strjoin(new, *ctn);
	free(*ctn);
	free(new);
	free(*flag);
	return (env);
}
