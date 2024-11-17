/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:25:10 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/17 16:13:38 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_is_die(t_parm *parm, t_philo *philo, int this_time)
{
	if (philo->timer >=parm->info->to_die)
	{
		pthread_mutex_lock(&parm->mutex->died_mutex);
		parm->info->is_died = 1;
		printing(parm->mutex->printf_mutex, "died", philo->index, this_time);
		pthread_mutex_unlock(&parm->mutex->died_mutex);
		
	}
}

void *do_threed_philo(void *ptr)
{
	// sleep(2);
	t_parm *parm;
	t_philo *philo;
	t_fork *fork_right;
	t_fork *fork_left;
	t_info	*info;
	int	this_time;
	int	last_time;
	parm = (t_parm *)ptr;
	this_time = 0;
	info = parm->info;
	write(1, "uuuuuuuuuu\n", 11);
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
		philo = philo->next_philo;
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
	}
	parm->info->last_philo_got_it++;
	pthread_mutex_unlock(&parm->mutex->last_philo_mutex);
	while (1)
	{
		if (info->is_died == 1)
			break;
		printf("%s","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
		// sleep(1);
		this_time = get_cur_time_millscd(info);
		// sleep(1);

		if (this_time == last_time)
			continue ;
		last_time = this_time;
		if (philo->is_eat_sleep == 0 && philo->is_eat == 0)
		{
			printf("%s","philo->is_eat_sleep == 0 && philo->is_eat == 0\n");
			
			//cheak if can get the fork_right && fork_left
			// mutex lock right && left
			philo->timer++;
			pthread_mutex_lock(&fork_right->fork_mutex);
			printf("%s","pthread_mutex_lock\n");
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
			printf("%s","philo->is_eat_sleep == 0 && philo->is_eat == 1\n");

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
			printf("%s","philo->is_eat_sleep == 1\n");

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
	t_philo	*next_philo;
	int is_error;
	int i;
	write(1, "uuuuuuuuuu\n", 11);
	
	i = 0;
	next_philo = parm->philo;
	is_error = init_pthread(&p, parm->info);
	write(1, "uuuuuuuuuu\n", 11);

	printf("%p\n", p);
	if (is_error == -2)
		return (-1);
	parm->pthrd = p;
	write(1, "uuuuuuuuuu\n", 11);

	is_error = init_threads(parm);
	write(1, "uuuuuuuuuu\n", 11);

	if (is_error == -1)
		return (-1);
	init_philo(parm);
	write(1, "uuuuuuuuuu\n", 11);

	while (i < parm->info->philo_count)
	{
		is_error = pthread_create(&p[i], NULL, &do_threed_philo, (void *)parm);
		if (is_error != 0)
			return (-1);
		i++;
	}
	// sleep(3);
	i = 0;
	while (i < parm->info->philo_count)
	{
		is_error = pthread_join(p[i], NULL);
		if (is_error != 0)
			return (-1);
		i++;
	}
	return (0);
}
