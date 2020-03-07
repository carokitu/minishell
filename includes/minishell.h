/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:50:44 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/16 18:03:18 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libftprintf.h"
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define FIRST_LETTERS "ecsu"

typedef struct		s_mini
{
	char	**env;
	char	**path;
	char	**flags;
	char	*cmd;
	char	**tmp_env;
	char	*previous_path;
	int		pathon;
	int		ipath;
	int		flagson;
	int		skipenv;
	int		envon;
	int		envon2;
	int		unenv;
	int		gp_nbr;
	int		exit;
}					t_mini;

int					mn_cd(t_mini *infos);
int					mn_envadd(char *arg);
int					mn_enverror(char arg);
int					mn_env(t_mini *infos);
int					mn_echo(t_mini *infos);
int					mn_read(t_mini *infos);
int					mn_envu(t_mini *infos);
int					mn_isexc(t_mini *infos);
int					mn_printenv(char **env);
int					mn_checkenv1(char *str);
int					mn_eargenv(char *error);
int					mn_setenv(t_mini *infos);
int					mn_getpath(t_mini *infos);
int					mn_cderror(t_mini *infos);
int					mn_unsetenv(t_mini *infos);
int					mn_checkarg(t_mini *infos);
int					mn_setenvarg(t_mini *infos);
int					mn_unsetenv2(t_mini *infos);
int					mn_checkenv(t_mini *infos);
int					mn_checkdolls(t_mini *infos);
int					mn_allouenv_2(t_mini *infos);
int					mn_treatbinary(t_mini *infos);
int					mn_setenverror(t_mini *infos);
int					mn_envbin(t_mini *infos, int *i);
int					mn_addenv(t_mini *infos, char *arg);
int					mn_getarg(t_mini *infos, char *line);
int					mn_envpath(t_mini *infos, char **arg);
int					mn_getline(char **env, char *str, int size);
int					mn_treat(t_mini *infos, char **line, char **save);
int					mn_getline_env(t_mini *infos, char *str, int size);
int					mn_envbinaire(t_mini *infos, char **arg, char *barg);
int					mn_whilesave(t_mini *infos, char **line, char **save);
void				mn_tirerror1(char *path);
void				mn_prompt(t_mini *infos);
void				mn_tmpenv(t_mini *infos);
void				mn_oldpwd(t_mini *infos);
void				mn_error_cd1(char *path);
void				mn_allouenv(t_mini *infos);
void				mn_freeflags(t_mini *infos);
void				mn_allouenv_1(t_mini *infos);
void				mn_checkflags(t_mini *infos);
void				mn_getnewenv(t_mini *infos, int a);
void				mn_freesave(char **save, int to_free);
void				mn_checksep(char **line, char **save);
void				mn_error_cd2(char *path, struct stat *in);
void				mn_setenv2bis(t_mini *infos, int i, int *a, char **save);
void				mn_freethree(char **un, char **deux, char **trois);
char				**mn_dupstr(char **str);
char				*mn_dolls2(char **flag, int i, int start, char **ctn);
char				*mn_printdolls(char **un, char **deux, char **trois, t_mini
					*infos);

#endif
