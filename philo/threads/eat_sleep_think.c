/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:33:08 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/25 20:33:39 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_sleaping(t_parm *parm, t_philo *philo, t_info *info,
		int this_time)
{
	philo->timer++;
	if (philo->timer > info->to_sleep)
	{
		philo->is_eat_sleep = 0;
		philo->timer = 0;
		printing(parm, "is thinking", philo->index, this_time);
	}
}

t_philo	*philo_eating(t_parm *parm, t_philo *philo, t_info *info, int this_time)
{
	philo->timer++;
	if (philo->timer > info->to_eat)
	{
		philo->is_eat_sleep = 1;
		philo->timer = 0;
		pthread_mutex_lock(&philo->fork_right->fork_mutex);
		philo->fork_right->is_allowed = 1;
		pthread_mutex_unlock(&philo->fork_right->fork_mutex);
		pthread_mutex_lock(&philo->fork_left->fork_mutex);
		philo->fork_left->is_allowed = 1;
		pthread_mutex_unlock(&philo->fork_left->fork_mutex);
		philo->how_many_eat++;
		philo->is_eat = 0;
		printing(parm, "is sleeping", philo->index, this_time);
	}
	return (philo);
}
void	take_forks_eating(t_parm *parm, t_philo *philo, int this_time)
{
	philo->fork_right->is_allowed = 0;
	philo->fork_right->last_who_eating = philo->index;
	printing(parm, "has taken a fork", philo->index, this_time);
	philo->fork_left->is_allowed = 0;
	philo->fork_left->last_who_eating = philo->index;
	printing(parm, "has taken a fork", philo->index, this_time);
	philo->is_eat = 1;
	printing(parm, "is eating", philo->index, this_time);
	philo->next_die_timer = 0;
}

t_philo	*cheak_can_eat(t_parm *parm, t_philo *philo, int this_time)
{
	pthread_mutex_lock(&philo->fork_right->fork_mutex);
	pthread_mutex_lock(&philo->fork_left->fork_mutex);
	if (philo->fork_right->is_allowed == 1 && philo->fork_left->is_allowed == 1)
	{
		pthread_mutex_lock(&philo->fork_right->last_eating_mutex);
		if (philo->fork_right->last_who_eating != philo->index)
		{
			pthread_mutex_lock(&philo->fork_left->last_eating_mutex);
			if (philo->fork_left->last_who_eating != philo->index)
			{
				take_forks_eating(parm, philo, this_time);
			}
			pthread_mutex_unlock(&philo->fork_left->last_eating_mutex);
		}
		pthread_mutex_unlock(&philo->fork_right->last_eating_mutex);
	}
	pthread_mutex_unlock(&philo->fork_left->fork_mutex);
	pthread_mutex_unlock(&philo->fork_right->fork_mutex);
	return (philo);
}

t_philo	*eating_sleeping_thinking(t_parm *parm, t_philo *philo, t_info *info, int this_time)
{
	if (info->philo_count > 1)
	{
		if (philo->is_eat_sleep == 0 && philo->is_eat == 0)
			philo = cheak_can_eat(parm, philo, this_time);
		else if (philo->is_eat_sleep == 0 && philo->is_eat == 1)
			philo = philo_eating(parm, philo, info, this_time);
		else if (philo->is_eat_sleep == 1)
			philo_sleaping(parm, philo, info, this_time);
	}
	return (philo);
}
