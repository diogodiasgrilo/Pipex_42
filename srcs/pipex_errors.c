/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:28:35 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/02 15:26:58 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	custm_err_msg(char *error)
{
	write(2, error, ft_strlen(error));
	return (1);
}

void	err_msg_exit(char *error)
{
	perror(error);
	exit(1);
}

void	cmd_error(char *cmd)
{
	char	*temp1;
	char	*temp2;

	if (cmd[0] == '/')
		temp1 = ft_strjoin(ERR_CMD2, cmd);
	else
		temp1 = ft_strjoin(ERR_CMD1, cmd);
	temp2 = ft_strjoin(temp1, "\n");
	write(2, temp2, ft_strlen(temp2));
	free(temp1);
	free(temp2);
}

void	check_file_error(t_info *info, int argc, char *argv[])
{
	info->infile = open(argv[1], O_RDONLY);
	info->outfile = open(argv[argc - 1], O_APPEND | \
			O_CREAT | O_RDWR, 0644);
	if (info->infile < 0)
		custm_err_msg("infile: No such file or directory\n");
	if (info->outfile < 0)
		custm_err_msg("outfile: No such file or directory\n");
	if (info->infile >= 0)
		close(info->infile);
	if (info->outfile >= 0)
		close(info->outfile);
	if (info->outfile < 0 || info->infile < 0)
	{
		free(info);
		exit (1);
	}
}
