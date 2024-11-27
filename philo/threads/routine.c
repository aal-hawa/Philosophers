/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:13:04 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/27 16:32:23 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	loop_philo(t_parm *parm, t_philo *philo, t_info *info, int this_time)
{
	int	last_time;

	last_time = -1;
	while (1)
	{
		pthread_mutex_lock(&parm->mutex->died_mutex);
		if (info->is_died == 1)
		{
			pthread_mutex_unlock(&parm->mutex->died_mutex);
			break ;
		}
		pthread_mutex_unlock(&parm->mutex->died_mutex);
		if (info->how_many_eat > 0 && philo->how_many_eat == info->how_many_eat)
			break ;
		this_time = get_cur_time_millscd(info);
		if (last_time == this_time)
			continue ;
		last_time = this_time;
		philo = eating_sleeping_thinking(parm, philo, info, this_time);
		philo->curr_die_timer++;
		philo->next_die_timer++;
		philo_is_die(parm, philo, this_time);
		usleep(100);
	}
}

void	*do_threed_philo(void *ptr)
{
	t_parm	*parm;
	t_philo	*philo;
	int		this_time;

	parm = (t_parm *)ptr;
	this_time = 0;
	philo = NULL;
	philo = select_philo_fork(parm, philo, parm->info);
	loop_philo(parm, philo, parm->info, this_time);
	return (NULL);
}
