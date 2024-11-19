/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:13:04 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/19 11:43:10 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_sleaping(t_philo *philo, t_info *info)
{
		philo->timer++;
	if (philo->timer >= info->to_sleep)
	{
		philo->is_eat_sleep = 0;
		philo->timer = 0;
	}
}

void	philo_eating(t_parm *parm, t_philo *philo, t_fork *fork_left, t_fork *fork_right, t_info *info, int this_time)
{
	philo->timer++;
	if (philo->timer >= info->to_eat)
	{
		philo->is_eat_sleep = 1;
		philo->timer = 0;
		pthread_mutex_lock(&fork_right->fork_mutex);
		pthread_mutex_lock(&fork_left->fork_mutex);
		fork_right->is_allowed = 1;
		fork_left->is_allowed = 1;
		philo->is_eat = 0;
		// mutex unlock right && left
		printing(parm->mutex->printf_mutex, "is sleeping", philo->index, this_time);
		pthread_mutex_unlock(&fork_right->fork_mutex);
		pthread_mutex_unlock(&fork_left->fork_mutex);
	}
}

void	cheak_can_eat(t_parm *parm, t_philo *philo, t_fork *fork_left, t_fork *fork_right, int this_time)
{
	philo->timer++;
	pthread_mutex_lock(&fork_right->fork_mutex);
	pthread_mutex_lock(&fork_left->fork_mutex);

	if (fork_right->is_allowed == 1 && fork_left->is_allowed == 1)
	{
		fork_right->is_allowed = 0;
		printing(parm->mutex->printf_mutex, "has taken a fork", philo->index, this_time);
		fork_left->is_allowed = 0;
		printing(parm->mutex->printf_mutex, "has taken a fork", philo->index, this_time);
		philo->is_eat = 1;
		printing(parm->mutex->printf_mutex, "is eating", philo->index, this_time);
	}
	// mutex unlock right && left
	pthread_mutex_unlock(&fork_right->fork_mutex);
	pthread_mutex_unlock(&fork_left->fork_mutex);
}

void	select_philo_fork(t_parm *parm, t_philo *philo, t_fork *fork_left, t_fork *fork_right, t_info *info)
{
	pthread_mutex_lock(&parm->mutex->last_philo_mutex);
	philo = parm->philo;
	philo->timer = 0;
	philo->is_eat = 0;
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
			break ;
		fork_left = fork_left->next_fork;
	}
	while (fork_right)
	{
		if (fork_right->index == philo->index)
			break ;
		fork_right = fork_right->next_fork;
		if (!fork_right && info->philo_count > 1 )
		{
			fork_right = parm->fork;
			break ;
		}
	}
	// info->last_philo_got_it++;
	pthread_mutex_unlock(&parm->mutex->last_philo_mutex);
}

void	loop_philo(t_parm *parm, t_philo *philo, t_fork *fork_left, t_fork *fork_right, t_info *info, int this_time)
{

	while (1)
	{
		if (info->is_died == 1)
			break;
		this_time = get_cur_time_millscd(info);
		if (philo->is_eat_sleep == 0 && philo->is_eat == 0){
			cheak_can_eat(parm, philo, fork_left, fork_right, this_time);
		}
		else if (philo->is_eat_sleep == 0 && philo->is_eat == 1){
			philo_eating(parm, philo, fork_left, fork_right, info, this_time);
	}
		else if (philo->is_eat_sleep == 1)
		{
			// time of sleaping++
				philo->timer++;
			if (philo->timer >= info->to_sleep)
			{
				philo->is_eat_sleep = 0;
				philo->timer = 0;
			}
		}
		philo_is_die(parm, philo, this_time);
	}
}


void *do_threed_philo(void *ptr)
{
	t_parm *parm;
	t_philo philo;
	t_fork fork_right;
	t_fork fork_left;
	t_info	*info;
	
	int	this_time;
	parm = (t_parm *)ptr;
	this_time = 0;
	info = parm->info;
	select_philo_fork(parm, &philo, &fork_left, &fork_right, info);
	loop_philo(parm, &philo, &fork_left, &fork_right, info, this_time);
	return (NULL);
}
