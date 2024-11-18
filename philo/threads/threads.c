/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:25:10 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/18 16:42:27 by aal-hawa         ###   ########.fr       */
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
	
	i = 0;
	next_philo = parm->philo;
	is_error = init_pthread(&p, parm->info);
	printf("%p\n", p);
	if (is_error == -2)
		return (-1);
	parm->pthrd = p;

	is_error = init_threads(parm);
	if (is_error == -1)
		return (-1);
	init_philo(parm);
	while (i < parm->info->philo_count)
	{
		is_error = pthread_create(&p[i], NULL, &do_threed_philo, (void *)parm);
		if (is_error != 0)
			return (-1);
		i++;
	}
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
