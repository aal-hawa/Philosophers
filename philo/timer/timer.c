/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:57:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/10 17:30:39 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	time_now(t_parm *parm)
{
	t_info *info = parm->info;
	t_mutex *mutex = parm->mutex;
	while (1)
	{
		// pthread_mutex_lock(&mutex->timer_mutex);
		if (info->timer_unsleep >= 2147483647)
		{
			// pthread_mutex_unlock(&mutex->timer_mutex);
			break;
		}
		// pthread_mutex_unlock(&mutex->timer_mutex);
		
		usleep(1);
		pthread_mutex_lock(&mutex->timer_mutex);
		info->timer_unsleep++;
		pthread_mutex_unlock(&mutex->timer_mutex);

	}
}