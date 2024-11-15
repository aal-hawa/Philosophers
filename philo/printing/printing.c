/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:56 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/15 17:40:54 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	error_massege(char *str, int is_error)
{
	
}

void	recursive_nbr(int n, int fd)
{
	char	c;

	if (n < 0)
		return ;
	if (n > 9)
	{
		recursive_nbr(n / 10, fd);
		recursive_nbr(n % 10, fd);
	}
	else
	{
		c = n + '0';
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	recursive_nbr(n, fd);
}

void	ft_putstr_fd(char *s, int philo_nbr, int is_malloc, int timer)
{
	int	i;

	if (!s)
		return ;
	ft_putnbr_fd(timer, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo_nbr, 1);
	write(1, " ", 1);
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	if (is_malloc == 2 || is_malloc == -1)
		write(1, "\n", 1);
	if (is_malloc == 1 || is_malloc == 2)
		free_char(s);
}

void	printing(pthread_mutex_t mutex, char *s, int philo_nbr, int timer)
{
	pthread_mutex_lock(&mutex);
	ft_putstr_fd(s, philo_nbr, -1, timer);
	pthread_mutex_unlock(&mutex);
}