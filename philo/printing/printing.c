/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:56 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/26 11:06:26 by aal-hawa         ###   ########.fr       */
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

void	printing_died(t_parm *parm, char *s, int philo_nbr, int timer)
{
	pthread_mutex_lock(&parm->mutex->printf_mutex);
	printf("%d %d %s\n", timer, philo_nbr, s);
	pthread_mutex_unlock(&parm->mutex->printf_mutex);
}

void	printing(t_parm *parm, char *s, int philo_nbr, int timer)
{
	int	is_can_print;

	is_can_print = 1;
	pthread_mutex_lock(&parm->mutex->died_mutex);
	if (parm->info->is_died == 1)
		is_can_print = 0;
	pthread_mutex_unlock(&parm->mutex->died_mutex);
	if (is_can_print == 0)
		return ;
	pthread_mutex_lock(&parm->mutex->printf_mutex);
	printf("%d %d %s\n", timer, philo_nbr, s);
	pthread_mutex_unlock(&parm->mutex->printf_mutex);
}
