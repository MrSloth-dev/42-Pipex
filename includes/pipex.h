/*                                                                            */
/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:05:55 by joao-pol          #+#    #+#             */
/*   Updated: 2024/07/10 16:07:43 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../includes/libft.h"

# define SUCCESS 0
# define INPUT_ERROR 1
# define INFILE_ERROR 1
# define OUTFILE_ERROR 1
# define PIPE_ERROR 1
# define FORK_ERROR 1
# define FD_STDOUT_CHILD 1
# define FD_STDIN_CHILD 1
# define FD_STDOUT_PARENT 1
# define FD_STDIN_PARENT 1
# define MEMORY_ERROR 1
# define EXECVE_ERROR_CHILD 1
# define EXECVE_ERROR_PARENT 1

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		error_pipe[2];
	int		pipe[2];
	int		infile;
	int		outfile;
	char	error_msg[256];
	char	**cmd_paths;
	char	**cmd_args;
	char	*find_path;
	char	*cmd;
}	t_pipex;

void	ft_pipex(t_pipex *pipex, char *argv[], char *envp[]);
void	ft_free_files(t_pipex *pipex);
void	ft_free_split(char **str, size_t index);
int		ft_check_quotes(char **cmd_args);
void	ft_child_process(t_pipex pipex, char **argv, char **envp);
void	ft_parent_process(t_pipex pipex, char **argv, char **envp);
int		ft_get_cmd(t_pipex *pipex);
int		ft_error_msg(t_pipex *pipex, char *error_msg, int ERRNO);
char	*ft_find_path(char *envp[]);
int		ft_init_pipex(t_pipex *pipex, char *argv[], char *envp[]);
void	ft_perror(char **cmd_args, char *error, int code, t_pipex *pipex);
char	*ft_strjoin_free(char const *s1, char const *s2);

#endif // PIPEX_H
