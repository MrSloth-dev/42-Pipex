/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:05:13 by joao-pol          #+#    #+#             */
/*   Updated: 2024/07/17 13:06:03 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/libft/libft.h"
#include "pipex.h"

/*
    [parent]
     |     \
     |      \     [parent] gets a pid ->pid1
     |       \
   [child(1)]   	[parent]

[child(1)] will 		|     \
receive the   			|      \    [parent] gets a pid -> pid2
input		  			|       \
			  		child(2)]    [parent] 
					Wait for the children to end waitpid(pid1 and pid2) ;

                child(2) will change the output
*/
char	*ft_find_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) != 0)
			envp++;
		else
			return (*envp + 5);
	}
	return (NULL);
}

// Get the full path to the command binary
int	ft_get_cmd(t_pipex *pipex)
{
	char	*temp;
	int		i;
	int		err;

	i = 0;
	temp = NULL;
	if (!pipex->cmd_args || !pipex->cmd_args[0])
		return (ft_putstr_fd(pipex->cmd_args[0], 2), -1);
	while (pipex->cmd_paths[i])
	{
		temp = ft_strjoin(pipex->cmd_paths[i], "/");
		temp = ft_strjoin_free(temp, ft_strdup(pipex->cmd_args[0]));
		err = access(temp, X_OK);
		if (err == 0)
		{
			pipex->cmd = temp;
			return (0);
		}
		free(temp);
		i++;
	}
	ft_putstr_fd(pipex->cmd_args[0], 2);
	return (-1);
}

int	ft_check_quotes(char **cmd_args)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (cmd_args[i])
	{
		j = 0;
		count = 0;
		while (cmd_args[i][j])
		{
			if (cmd_args[i][j] == '\'')
				count++;
			j++;
		}
		if (count % 2 != 0)
			return (ft_free_split(cmd_args, j), 0);
		i++;
	}
	return (1);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	join = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!join)
		return (free((void *)s1), free((void *)s2), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	free((void *)s1);
	free((void *)s2);
	return (join);
}
