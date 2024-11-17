/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:57:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/17 13:38:20 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_cur_time_millscd(t_info *info)
{
	struct timeval cur_time;
	long long time_sub;
	if (info->is_get_timer == 0)
	{
		gettimeofday(&info->fst_time, NULL); 
		info->is_get_timer = 1;
	}
	printf("%s","zzzzzzzzzzzzzzzzzzzzzzz\n");
	gettimeofday(&cur_time, NULL); 
	printf("%d\n",cur_time.tv_usec);
	printf("%d\n",info->fst_time.tv_usec);
	printf("%s","qqqqqqqqqqqqqqqqqqqqqqqq\n");

	time_sub = cur_time.tv_usec - info->fst_time.tv_usec;
	return ((int)(time_sub % 1000));
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