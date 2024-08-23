/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-pol <joao-pol@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:47:20 by joao-pol          #+#    #+#             */
/*   Updated: 2024/05/07 10:47:25 by joao-pol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H	

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <fcntl.h>

int		ft_printf(const char *str, ...);
int		ft_atoi(const char *rstr);
char	*ft_itoa(int nbr);
int		ft_uputnbr_fd(unsigned int nb, int fd);
int		ft_putchar_fd(char c, int fd);
int		ft_putnbr_fd(int nb, int fd);
int		ft_putstr_fd(char *str, int fd);
int		ft_puthex_fd(unsigned int nbr, char x, int fd);
int		ft_putpointer_fd(unsigned long long ptr, int fd);
char	*ft_strchr(const char *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);

//GET_NEXT_LINE
// void	ft_bzero(char *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*get_next_line(int fd);
char	*ft_cleanfile(char *str);
#endif
