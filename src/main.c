/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:24:05 by joao-pol          #+#    #+#             */
/*   Updated: 2024/08/08 12:53:10 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/libft/libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		error;

	error = 0;
	if (argc != 5)
		return (ft_putstr_fd("Error with Input", 2), INPUT_ERROR);
	error = ft_init_pipex(&pipex, argv, envp);
	if (error != SUCCESS)
		return (error);
	ft_pipex(&pipex, argv, envp);
	ft_free_files(&pipex);
	return (error);
}

int	ft_init_pipex(t_pipex *pipex, char *argv[], char *envp[])
{
	pipex->cmd_args = NULL;
	pipex->cmd_paths = NULL;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->pipe[0] = -1;
	pipex->pipe[1] = -1;
	if (pipex->infile == -1)
		exit (ft_error_msg(pipex, argv[1], INFILE_ERROR));
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		exit (ft_error_msg(pipex, argv[4], OUTFILE_ERROR));
	if (pipe(pipex->pipe) == -1)
		exit (ft_error_msg(pipex, "Error with Pipe ", PIPE_ERROR));
	pipex->find_path = ft_find_path(envp);
	pipex->cmd_paths = ft_split(pipex->find_path, ':');
	if (!pipex->cmd_paths)
		exit (ft_error_msg(pipex, "Error with cmd_paths", MEMORY_ERROR));
	return (SUCCESS);
}

void	ft_pipex(t_pipex *pipex, char *argv[], char *envp[])
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		ft_error_msg(pipex, "Error with fork", FORK_ERROR);
	else if (!pipex->pid1)
	{
		ft_child_process(*pipex, argv, envp);
	}
	waitpid(pipex->pid1, NULL, WNOHANG);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		ft_error_msg(pipex, "Error with fork", FORK_ERROR);
	if (pipex->pid2 == 0)
	{
		ft_parent_process(*pipex, argv, envp);
	}
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	close(pipex->outfile);
	waitpid(pipex->pid2, NULL, WNOHANG);
}

void	ft_child_process(t_pipex pipex, char **argv, char **envp)
{
	if (dup2(pipex.pipe[1], STDOUT_FILENO) == -1)
		ft_error_msg(&pipex, "Error with STDOUT in child", FD_STDOUT_CHILD);
	close(pipex.pipe[0]);
	if (dup2(pipex.infile, STDIN_FILENO) == -1)
		ft_error_msg(&pipex, "Error with STDIN in child", FD_STDIN_CHILD);
	pipex.cmd_args = ft_split(argv[2], ' ');
	if (ft_check_quotes(pipex.cmd_args) == 0)
		ft_error_msg(&pipex, "Error with EXECVE", EXECVE_ERROR_CHILD);
	if (ft_get_cmd(&pipex) == -1)
		ft_error_msg(&pipex, ": command not found\n", 127);
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		ft_error_msg(&pipex, pipex.cmd_args[0], 1);
}

void	ft_parent_process(t_pipex pipex, char **argv, char **envp)
{
	if (dup2(pipex.pipe[0], STDIN_FILENO) == -1)
		ft_error_msg(&pipex, "Error with STDOUT in parent", FD_STDOUT_PARENT);
	close(pipex.pipe[1]);
	if (dup2(pipex.outfile, STDOUT_FILENO) == -1)
		ft_error_msg(&pipex, "Error with STDIN in parent", FD_STDIN_PARENT);
	pipex.cmd_args = ft_split(argv[3], ' ');
	if (ft_check_quotes(pipex.cmd_args) == 0)
		ft_error_msg(&pipex, "Error with ", EXECVE_ERROR_PARENT);
	pipex.cmd = pipex.cmd_args[0];
	if (ft_get_cmd(&pipex) == -1)
		ft_error_msg(&pipex, ": command not found\n", 127);
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		ft_error_msg(&pipex, pipex.cmd_args[0], 1);
}
