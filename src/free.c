/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:06:02 by joao-pol          #+#    #+#             */
/*   Updated: 2024/07/17 12:41:42 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/libft/libft.h"
#include "pipex.h"

int	ft_error_msg(t_pipex *pipex, char *error_msg, int ERRNO)
{
	if (ERRNO != 127)
	{
		perror(error_msg);
	}
	else
		ft_putstr_fd(error_msg, 2);
	ft_free_files(pipex);
	if (ERRNO != SUCCESS)
		exit(ERRNO);
	return (ERRNO);
}

void	ft_free_files(t_pipex *pipex)
{
	int	i;

	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->pipe[0] != -1)
		close(pipex->pipe[0]);
	if (pipex->pipe[1] != -1)
		close(pipex->pipe[1]);
	i = 0;
	if (pipex->cmd_paths)
	{
		while (pipex->cmd_paths[i])
			free(pipex->cmd_paths[i++]);
		free(pipex->cmd_paths);
	}
	i = 0;
	if (pipex->cmd_args)
	{
		while (pipex->cmd_args[i])
			free(pipex->cmd_args[i++]);
		free(pipex->cmd_args);
	}
}

void	ft_free_split(char **str, size_t index)
{
	size_t	j;

	if (!str)
		return ;
	j = 0;
	while (j < index)
	{
		free(str[j]);
		j++;
	}
	free(str);
}
