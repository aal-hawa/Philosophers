/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:25:10 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/28 16:04:02 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_philo	*check_index_philo(t_parm *parm,
		t_philo *next_ph, t_philo *this_philo, int i)
{
	if (i == 0)
	{
		parm->philo = this_philo;
		next_ph = this_philo;
	}
	else
	{
		next_ph->next = this_philo;
		next_ph = next_ph->next;
	}
	return (next_ph);
}

static int	init_philo(t_parm *parm)
{
	int		i;
	t_philo	*this_philo;
	t_philo	*next_ph;

	i = 0;
	while (i < parm->info->philo_count)
	{
		this_philo = malloc(sizeof(t_philo));
		if (!this_philo)
			return (-1);
		this_philo->index = i + 1;
		this_philo->is_eat = 0;
		this_philo->is_eat_sleep = 0;
		this_philo->timer = 0;
		this_philo->is_get_fork_one = 0;
		this_philo->next_die_timer = 0;
		this_philo->how_many_eat = 0;
		this_philo->next = NULL;
		next_ph = check_index_philo(parm, next_ph, this_philo, i);
		i++;
	}
	return (0);
}

static int	init_pthread(pthread_t **p, t_info *info)
{
	*p = malloc(sizeof(pthread_t) * info->philo_count);
	if (!*p)
		return (-1);
	return (0);
}

static int	create_threads(t_parm *parm, pthread_t *p, int is_error)
{
	int	i;

	i = 0;
	while (i < parm->info->philo_count)
	{
		is_error = pthread_create(&p[i], NULL, &do_threed_philo, (void *)parm);
		if (is_error != 0)
			return (-6);
		i++;
	}
	i = 0;
	while (i < parm->info->philo_count)
	{
		is_error = pthread_join(p[i], NULL);
		if (is_error != 0)
			return (-7);
		i++;
	}
	return (is_error);
}

int	threads(t_parm *parm)
{
	pthread_t	*p;
	int			is_error;

	is_error = init_pthread(&p, parm->info);
	if (is_error != 0)
		return (is_error);
	parm->pthrd = p;
	is_error = init_threads(parm);
	if (is_error != 0)
		return (is_error);
	is_error = init_philo(parm);
	if (is_error != 0)
		return (-5);
	get_first_time_millscd(parm->info);
	is_error = create_threads(parm, p, is_error);
	return (0);
}
