/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:13:04 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/25 18:09:13 by aal-hawa         ###   ########.fr       */
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
			pthread_mutex_unlock(&philo->fork_left->last_eating_mutex);
		}
		pthread_mutex_unlock(&philo->fork_right->last_eating_mutex);
	}
	pthread_mutex_unlock(&philo->fork_left->fork_mutex);
	pthread_mutex_unlock(&philo->fork_right->fork_mutex);
	return (philo);
}

void	loop_philo(t_parm *parm, t_philo *philo, t_info *info, int this_time)
{
	int	last_time;

	last_time = -1;
	while (1)
	{
		pthread_mutex_lock(&parm->mutex->died_mutex);
		if ((info->is_died == 1 && info->how_many_eat == 0)
			|| (info->is_died == 1 && info->philo_count == 1))
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
		if (info->philo_count > 1)
		{
			if (philo->is_eat_sleep == 0 && philo->is_eat == 0)
				philo = cheak_can_eat(parm, philo, this_time);
			else if (philo->is_eat_sleep == 0 && philo->is_eat == 1)
				philo = philo_eating(parm, philo, info, this_time);
			else if (philo->is_eat_sleep == 1)
				philo_sleaping(parm, philo, info, this_time);
		}
		philo->curr_die_timer++;
		philo->next_die_timer++;
		philo_is_die(parm, philo, this_time);
		usleep(100);
	}
}

t_philo	*select_philo_fork(t_parm *parm, t_philo *philo, t_info *info)
{
	t_fork	*fork_right;
	t_fork	*fork_left;
	t_fork	*fork_swap;

	pthread_mutex_lock(&parm->mutex->last_philo_mutex);
	philo = parm->philo;
	fork_left = parm->fork;
	fork_right = parm->fork;
	while (philo)
	{
		if (philo->index == info->last_philo_got_it)
			break ;
		philo = philo->next;
	}
	while (fork_left)
	{
		if (fork_left->index == philo->index - 1)
		{
			philo->fork_left = fork_left;
			break ;
		}
		fork_left = fork_left->next;
	}
	while (fork_right)
	{
		if (fork_right->index == philo->index)
		{
			philo->fork_right = fork_right;
			break ;
		}
		fork_right = fork_right->next;
		if (!fork_right && info->philo_count > 1)
		{
			philo->fork_right = parm->fork;
			break ;
		}
	}
	if (philo->index % 2 != 0)
	{
		fork_swap = philo->fork_left;
		philo->fork_left = philo->fork_right;
		philo->fork_right = fork_swap;
	}
	info->last_philo_got_it++;
	pthread_mutex_unlock(&parm->mutex->last_philo_mutex);
	return (philo);
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
