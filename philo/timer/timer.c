/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:57:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/19 20:00:43 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_cur_time_millscd(t_info *info)
{
	struct timeval cur_time;
	long curr_time_sec;
	long curr_time_microsec;
	int	curr_time_millsecond;
	
	if (info->is_get_timer == 0)
	{
		info->is_get_timer = 1;
		gettimeofday(&info->fst_time, NULL);
	}
	gettimeofday(&cur_time, NULL);
	curr_time_sec = cur_time.tv_sec - info->fst_time.tv_sec;
	curr_time_microsec = cur_time.tv_usec - info->fst_time.tv_usec;
	curr_time_millsecond = (int)((curr_time_sec * 1000) + (curr_time_microsec / 1000));
	return (curr_time_millsecond);
}

// int	time_now(t_parm *parm)
// {
// 	t_info *info = parm->info;
// 	t_mutex *mutex = parm->mutex;
// 	while (1)
// 	{
// 		// pthread_mutex_lock(&mutex->timer_mutex);
// 		if (info->timer_unsleep >= 2147483647) // edit this later
// 		{
// 			// pthread_mutex_unlock(&mutex->timer_mutex);
// 			break;
// 		}
// 		// pthread_mutex_unlock(&mutex->timer_mutex);
		
// 		usleep(1);
// 		pthread_mutex_lock(&mutex->timer_mutex);
// 		info->timer_unsleep++;
// 		pthread_mutex_unlock(&mutex->timer_mutex);
// 		pthread_mutex_lock(&mutex->died_mutex);
// 		if (info->is_died == 1)
// 			break ;
// 		pthread_mutex_unlock(&mutex->died_mutex);
// 	}
// }