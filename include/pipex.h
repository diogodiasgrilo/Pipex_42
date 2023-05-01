/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:35:52 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/01 20:45:11 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_H
# define PIPEX_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

# define ERR_INFILE "infile"
# define ERR_OUTFILE "outfile"
# define ERR_INPUT "invalid number of arguments.\n"
# define ERR_PATHS "couldn't find paths.\n"
# define ERR_PIPE "pipe"
# define ERR_DUP2 "dup2 failed"
# define ERR_FORK "fork failed"
# define ERR_CMD1 "command not found: "
# define ERR_CMD2 "no such file or directory: "

typedef struct s_data
{
	char	**envp_paths;
	char	**args;
	char	*arg_path;
	int		pipe[2];
	int		i;
	int		pid;
	int		infile;
	int		outfile;
}			t_info;

void	cmd_error(char *cmd);
int		sort_arg(t_info *info);
void	shut_pipe(t_info *info);
int		check_char(t_info *info);
void	err_msg_exit(char *error);
void	free_split(char **strings);
int		custm_err_msg(char *error);
int		path_check(t_info *data, int j);
void	args_prep(t_info *info, char **argv);
void	handle_pipes(t_info *info, char **argv);
void	child_process(t_info *info, char **argv, char **envp);

#endif