/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:56 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/19 11:44:01 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	error_massege(char *str, int is_error)
{
	if (is_error == -1)
		return (-1);
	printf("%s\n", str);
	return (-1);
}

void	printing(pthread_mutex_t mutex, char *s, int philo_nbr, int timer)
{
	pthread_mutex_lock(&mutex);
	printf("%d %d %s\n", timer, philo_nbr, s);
	pthread_mutex_unlock(&mutex);
}