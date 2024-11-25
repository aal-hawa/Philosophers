/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_philo_forks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:28:58 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/25 20:30:24 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_fork	*select_left_forks(t_parm *parm, t_philo *philo, t_info *info, t_fork *fork_left)
{
	while (fork_left)
	{
		if (fork_left->index == philo->index - 1)
		{
			philo->fork_left = fork_left;
			break ;
		}
		fork_left = fork_left->next;
	}
	return (fork_left);
}

t_fork	*select_right_fork(t_parm *parm, t_philo *philo, t_info *info, t_fork *fork_right)
{
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
	return (fork_right);
}


t_philo	*select_philo(t_parm *parm, t_philo *philo, t_info *info)
{
	philo = parm->philo;
	while (philo)
	{
		if (philo->index == info->last_philo_got_it)
			break ;
		philo = philo->next;
	}
	return (philo);
}

t_philo	*select_philo_fork(t_parm *parm, t_philo *philo, t_info *info)
{
	t_fork	*fork_right;
	t_fork	*fork_left;
	t_fork	*fork_swap;

	pthread_mutex_lock(&parm->mutex->last_philo_mutex);
	fork_left = parm->fork;
	fork_right = parm->fork;
	philo = select_philo(parm, philo, info);
	fork_left = select_left_forks(parm, philo, info, fork_left);
	fork_right = select_right_fork(parm, philo, info, fork_right);
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
