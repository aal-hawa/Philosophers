/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:13:04 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/12/04 13:11:30 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	philo_is_die(t_parm *parm, t_philo **philo)
{
	int	is_can_print;

	is_can_print = 1;
	(*philo)->next_die_timer++;
	if ((*philo)->next_die_timer > parm->info->to_die)
	{
		pthread_mutex_lock(&parm->mutex->died_mutex);
		if (parm->info->is_died == 1)
			is_can_print = 0;
		parm->info->is_died = 1;
		pthread_mutex_unlock(&parm->mutex->died_mutex);
		if (is_can_print == 1)
			printing_died(parm, "died", (*philo)->index, (*philo)->this_time);
	}
}

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
		if (info->how_many_eat > 0
			&& (*philo)->how_many_eat == info->how_many_eat)
			break ;
		eating_sleeping_thinking(parm, philo, info);
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
	if (philo->index % 2 != 0)
		usleep(100);
	loop_philo(parm, &philo, parm->info);
	return (NULL);
}
