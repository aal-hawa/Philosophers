/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:25:10 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/26 11:13:46 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_is_die(t_parm *parm, t_philo *philo, int this_time)
{
	int	is_can_print;

	is_can_print = 1;
	if (philo->next_die_timer > parm->info->to_die)
	{
		pthread_mutex_lock(&parm->mutex->died_mutex);
		if (parm->info->is_died == 1)
			is_can_print = 0;
		parm->info->is_died = 1;
		pthread_mutex_unlock(&parm->mutex->died_mutex);
		if (is_can_print == 1)
			printing_died(parm, "died", philo->index, this_time);
	}
}

int	init_pthread(pthread_t **p, t_info *info)
{
	*p = malloc(sizeof(pthread_t) * info->philo_count);
	if (!*p)
		return (-1);
	return (0);
}

int	create_threads(t_parm *parm, pthread_t *p, int is_error)
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
