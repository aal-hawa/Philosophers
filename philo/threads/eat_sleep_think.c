/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:33:08 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/27 19:13:39 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	philo_sleaping(t_parm *parm, t_philo **philo)
{
	(*philo)->is_eat_sleep = 0;
	(*philo)->timer = 0;
	printing(parm, "is thinking", (*philo)->index, (*philo)->this_time);
	// (*philo)->timer++;
	// if ((*philo)->timer > info->to_sleep)
	// {
	// }
}

static void	philo_eating(t_parm *parm, t_philo **philo, t_info *info)
{
	(*philo)->is_eat_sleep = 1;
	(*philo)->timer = 0;
	pthread_mutex_lock(&(*philo)->fork_right->fork_mutex);
	(*philo)->fork_right->is_allowed = 1;
	pthread_mutex_unlock(&(*philo)->fork_right->fork_mutex);
	pthread_mutex_lock(&(*philo)->fork_left->fork_mutex);
	(*philo)->fork_left->is_allowed = 1;
	pthread_mutex_unlock(&(*philo)->fork_left->fork_mutex);
	(*philo)->how_many_eat++;
	(*philo)->is_eat = 0;
	if (info->how_many_eat > 0 && (*philo)->how_many_eat == info->how_many_eat)
		return ;
	printing(parm, "is sleeping", (*philo)->index, (*philo)->this_time);
	// (*philo)->timer++;
	// if ((*philo)->timer > info->to_eat)
	// {
	// }
}

static void	take_forks_eating(t_parm *parm, t_philo **philo)
{
	(*philo)->fork_right->is_allowed = 0;
	(*philo)->fork_right->last_who_eating = (*philo)->index;
	printing(parm, "has taken a fork", (*philo)->index,(*philo)->this_time);
	(*philo)->fork_left->is_allowed = 0;
	(*philo)->fork_left->last_who_eating = (*philo)->index;
	printing(parm, "has taken a fork", (*philo)->index, (*philo)->this_time);
	(*philo)->is_eat = 1;
	printing(parm, "is eating", (*philo)->index, (*philo)->this_time);
	(*philo)->next_die_timer = 0;
}

static void	cheak_can_eat(t_parm *parm, t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->fork_right->fork_mutex);
	if ((*philo)->fork_right->is_allowed == 1)
	{
		pthread_mutex_lock(&(*philo)->fork_left->fork_mutex);
		if ((*philo)->fork_left->is_allowed == 1)
		{
			pthread_mutex_lock(&(*philo)->fork_right->last_eating_mutex);
			if ((*philo)->fork_right->last_who_eating != (*philo)->index)
			{
				pthread_mutex_lock(&(*philo)->fork_left->last_eating_mutex);
				if ((*philo)->fork_left->last_who_eating != (*philo)->index)
				{
					take_forks_eating(parm, philo);
				}
				pthread_mutex_unlock(&(*philo)->fork_left->last_eating_mutex);
			}
			pthread_mutex_unlock(&(*philo)->fork_right->last_eating_mutex);
		}
		pthread_mutex_unlock(&(*philo)->fork_left->fork_mutex);
	}
	pthread_mutex_unlock(&(*philo)->fork_right->fork_mutex);
}

void	eating_sleeping_thinking(t_parm *parm,
		t_philo **philo, t_info *info)
{
	if (info->philo_count > 1)
	{
		if ((*philo)->is_eat_sleep == 0 && (*philo)->is_eat == 0)
			cheak_can_eat(parm, philo);
		else
		{
			(*philo)->timer++;
			if ((*philo)->is_eat_sleep == 0 && (*philo)->is_eat == 1
				&& (*philo)->timer > info->to_eat)
				philo_eating(parm, philo, info);
			else if ((*philo)->is_eat_sleep == 1 && (*philo)->timer > info->to_sleep)
				philo_sleaping(parm, philo);
		}
		return ;
	}
	if ((*philo)->is_get_fork_one == 1)
		return ;
	(*philo)->is_get_fork_one = 1;
	printing(parm, "has taken a fork", (*philo)->index, (*philo)->this_time);
}
