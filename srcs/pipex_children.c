/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:20:12 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/02 15:09:59 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_info *info, char **argv, char **envp)
{
	info->pid = fork();
	if (info->pid < 0)
		err_msg_exit(ERR_FORK);
	else if (info->pid == 0)
	{
		handle_pipes(info, argv);
		execve(info->arg_path, info->args, envp);
	}
}

void	handle_pipes(t_info *info, char **argv)
{
	if (info->i == 2)
	{
		info->infile = open(argv[1], O_RDONLY);
		close(info->pipe[0]);
		dup2(info->infile, STDIN_FILENO);
		dup2(info->pipe[1], STDOUT_FILENO);
		close(info->infile);
	}
	else if (info->i == 3)
	{
		info->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (info->outfile < 0)
			exit (1);
		close(info->pipe[1]);
		dup2(info->outfile, STDOUT_FILENO);
		dup2(info->pipe[0], STDIN_FILENO);
		close(info->outfile);
	}
	shut_pipe(info);
}
