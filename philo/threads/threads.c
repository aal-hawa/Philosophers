/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:25:10 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/15 16:25:01 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_is_die(t_parm *parm, int this_time)
{
	t_philo *philo;
	t_info	*info;
	
	if (philo->timer >= info->to_die)
	{
		pthread_mutex_lock(&parm->mutex->died_mutex);
		info->is_died = 1;
		printing(parm->mutex->printf_mutex, "died", philo->index, this_time);
		pthread_mutex_unlock(&parm->mutex->died_mutex);
		
	}
}

void *do_threed_philo(t_parm *parm)
{
	t_philo *philo;
	t_fork *fork_right;
	t_fork *fork_left;
	t_info	*info;
	unsigned long	this_time;
	
	philo->timer = 0;
	philo->is_eat = 0;
	this_time = 0;
	pthread_mutex_lock(&parm->mutex->last_philo_mutex);
	philo = parm->philos->philo;  // git this with the correct philo
	parm->philos->last_philo_got_it++;
	pthread_mutex_unlock(&parm->mutex->last_philo_mutex);
	while (1)
	{
		if (info->is_died == 1)
			break;
		if (this_time == info->timer_unsleep)
			continue ;
		this_time = info->timer_unsleep;
		if (philo->is_eat_sleep == 0 && philo->is_eat == 0)
		{
			//cheak if can get the fork_right && fork_left
			// mutex lock right && left
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
		else if (philo->is_eat_sleep == 0 && philo->is_eat == 1)
		{
			// time of eating ++
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
		philo_is_die(philo, this_time);
	}
	return (NULL);
}
int	init_pthread(pthread_t **p, t_info *info)
{
	*p = malloc(sizeof(pthread_t) * info->philo_count);
	if (!*p)
		return (-1);
	return (0);
}

int	threads(t_parm *parm)
{
	pthread_t *p;
	int is_error;
	int i;
	
	i = 0;
	is_error = init_pthread(&p, parm->info);
	if (is_error == -1)
		return (-1);
	is_error = init_threads(parm);
	if (is_error == -1)
		return (-1);
	while (i < parm->info->philo_count)
	{
		pthread_create(&p[i], NULL, &do_threed_philo, parm);
		i++;
	}
	i = 0;
	while (i < parm->info->philo_count)
	{
		pthread_join(p[i], NULL);
		i++;
	}
	return (0);
}
