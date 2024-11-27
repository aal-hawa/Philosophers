/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:13:04 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/27 18:08:14 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	loop_philo(t_parm *parm, t_philo **philo, t_info *info)
{
	int	last_time;

	last_time = -1;
	while (1)
	{
		(*philo)->this_time = get_cur_time_millscd(info);
		if (last_time == (*philo)->this_time)
		{
			usleep(50);
			continue ;
		}
		last_time = (*philo)->this_time;
		pthread_mutex_lock(&parm->mutex->died_mutex);
		if (info->is_died == 1)
		{
			pthread_mutex_unlock(&parm->mutex->died_mutex);
			break ;
		}
		pthread_mutex_unlock(&parm->mutex->died_mutex);
		if (info->how_many_eat > 0 && (*philo)->how_many_eat == info->how_many_eat)
			break ;
		eating_sleeping_thinking(parm, philo, info);
		(*philo)->next_die_timer++;
		philo_is_die(parm, philo);
	}
}

void	*do_threed_philo(void *ptr)
{
	t_parm	*parm;
	t_philo	*philo;

	parm = (t_parm *)ptr;
	philo = NULL;
	select_philo_fork(parm, &philo, parm->info);
	philo->this_time = 0;
	loop_philo(parm, &philo, parm->info);
	return (NULL);
}
