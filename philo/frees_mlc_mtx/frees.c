/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:58:04 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/12/05 14:48:16 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	free_forks(t_parm *parm)
{
	t_fork	*this_fork;
	t_fork	*next_fork;

	this_fork = parm->fork;
	while (this_fork)
	{
		next_fork = this_fork->next;
		pthread_mutex_destroy(&this_fork->fork_mutex);
		pthread_mutex_destroy(&this_fork->last_eating_mutex);
		free(this_fork);
		this_fork = next_fork;
	}
}

static void	destroy_mutexs(t_parm *parm)
{
	if (parm->mutex->printf_mutex_check == 1)
		pthread_mutex_destroy(&parm->mutex->printf_mutex);
	if (parm->mutex->timer_mutex_check == 1)
		pthread_mutex_destroy(&parm->mutex->timer_mutex);
	if (parm->mutex->last_philo_mutex_check == 1)
		pthread_mutex_destroy(&parm->mutex->last_philo_mutex);
	if (parm->mutex->died_mutex_check == 1)
		pthread_mutex_destroy(&parm->mutex->died_mutex);
	free(parm->mutex);
}

static void	free_philos(t_parm *parm)
{
	t_philo	*this_philo;
	t_philo	*next_philo;

	this_philo = parm->philo;
	next_philo = NULL;
	while (this_philo)
	{
		next_philo = this_philo->next;
		free(this_philo);
		this_philo = NULL;
		this_philo = next_philo;
	}
}

void	free_all_mlc(t_parm *parm, int is_error)
{
	if (is_error == -2)
		return ;
	free(parm->pthrd);
	free_forks(parm);
	if (is_error == -3)
	{
		free(parm->mutex);
		return ;
	}
	destroy_mutexs(parm);
	if (is_error == -4)
		return ;
	free_philos(parm);
	if (is_error == -5)
		return ;
}
