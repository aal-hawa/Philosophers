/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:14:37 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/25 20:05:28 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_fork	*check_index_fork(t_parm *parm, t_fork *next_fork, t_fork *this_fork, int i)
{
	if (i == 0)
	{
		parm->fork = this_fork;
		next_fork = this_fork;
	}
	else
	{
		next_fork->next = this_fork;
		next_fork = next_fork->next;
	}
	return (next_fork);
}

t_fork	*check_index_philo(t_philo *first_philo, t_philo *next_ph, t_philo *this_philo, int i)
{
	if (i == 0)
	{
		first_philo = this_philo;
		next_ph = this_philo;
	}
	else
	{
		next_ph->next = this_philo;
		next_ph = next_ph->next;
	}
	return (next_ph);
}
