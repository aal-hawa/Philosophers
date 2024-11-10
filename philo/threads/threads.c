/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:25:10 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/10 18:58:40 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *do_threed_philpo(t_parm *parm)
{
	t_philo *philo;
	t_fork *fork_right;
	t_fork *fork_left;
	t_info	*info;
	int	is_eat;
	int timer;
	int die_timer;

	timer = 0;
	is_eat = 0;
	
	pthread_mutex_lock(&parm->mutex->last_philo_mutex);
	philo = parm->philos->philo;  // git this with the correct philo
	parm->philos->last_philo_got_it++;
	pthread_mutex_unlock(&parm->mutex->last_philo_mutex);
	while (1)
	{
		if (info->is_died == 1)
			break;
		if (philo->is_eat_sleep == 0 && is_eat == 0)
		{
			//cheak if can get the fork_right && fork_left
			// mutex lock right && left
			if (fork_right->is_allowed == 1 && fork_left->is_allowed == 1)
			{
				fork_right->is_allowed = 0;
				fork_left->is_allowed = 0;
				is_eat = 1;
			}
			// mutex unlock right && left
		}
		else if (philo->is_eat_sleep == 0 && is_eat == 1)
		{
			// time of eating ++
			timer++;
			if (timer >= info->to_eat)
			{
				philo->is_eat_sleep = 1;
				timer = 0;
			}
		}
		else if (philo->is_eat_sleep == 1)
		{
			// time of sleaping++

		}
	}
}
int	init_pthread(pthread_t **p, t_info *info)
{
	
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
		pthread_create(&p[i], NULL, &do_threed_philpo, parm);
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
