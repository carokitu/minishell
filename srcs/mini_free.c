/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:59:18 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/22 13:41:29 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		mn_freeflags(t_mini *infos)
{
	int		i;

	i = -1;
	while (infos->flags[++i])
	{
		free(infos->flags[i]);
		infos->flags[i] = NULL;
	}
	free(infos->flags);
	infos->flagson = 0;
}
