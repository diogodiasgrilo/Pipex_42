/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_b_children.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:21:49 by diogpere          #+#    #+#             */
/*   Updated: 2023/04/28 17:00:21 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	child_process(pipex_info *info, int argc, char **argv, char **envp)
{
    info->pid = fork();
    if (info->pid < 0)
		err_msg_exit(ERR_FORK);
    else if (info->pid == 0)
	{
		handle_pipes(info, argc, argv);
		if (info->arg_path == 0)
			cmd_error_exit(info->args[0]);
		execve(info->arg_path, info->args, envp);
		exit(0);
	}
	info->old_pipe = dup(info->pipe[0]);
}

void	handle_pipes(pipex_info *info, int argc, char **argv)
{
	if (info->i == 2)
	{
		info->infile = open(argv[1], O_RDONLY);
		if (info->infile < 0)
			err_msg_exit(ERR_INFILE);
		dup2(info->infile, STDIN_FILENO);
		dup2(info->pipe[1], STDOUT_FILENO);
		close(info->infile);
	}
	if (info->i > 2 && info->i < argc - 2)
	{
		dup2(info->pipe[1], STDOUT_FILENO);
		dup2(info->old_pipe, STDIN_FILENO);
	}
	if (info->i == argc - 2)
	{
		info->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (info->outfile < 0)
			err_msg_exit(ERR_OUTFILE);
		dup2(info->outfile, STDOUT_FILENO);
		dup2(info->old_pipe, STDIN_FILENO);
		close(info->outfile);
	}
	shut_pipe(info);
}