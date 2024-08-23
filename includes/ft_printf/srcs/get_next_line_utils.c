/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:02:30 by joao-pol          #+#    #+#             */
/*   Updated: 2024/05/07 14:40:29 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_strdup(char *str)
{
	int		i;
	char	*result;

	if (!str || !*str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	result = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = str[i];
	return (result);
}

char	*ft_cleanfile(char *file)
{
	char	*result;
	int		length;
	int		i;
	int		j;

	if (!*file || !file)
	{
		free(file);
		return (NULL);
	}
	length = ft_strlen(file);
	i = 0;
	while (file[i] != '\0' && file[i] != '\n')
		i++;
	result = ft_calloc(((length - i) + 1), sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	while (file[i])
	{
		result[j++] = file[++i];
	}
	result[j] = '\0';
	free(file);
	return (result);
}
