/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:52:09 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/10 13:17:28 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"


t_fork	*init_fork(t_fork *fork)
{
	
}

t_forks	*init_forks(t_info *info)
{
	
}

t_mutex	*init_mutex(t_info *info)
{
	
}

t_mutexs	*init_mutexs(t_info *info)
{
	
}

int	init_threads(t_parm *parm)
{
	parm->info->forks = init_forks(parm->info);
	if (!parm->info->forks)
		return (-1);
	parm->info->mutexs = init_mutexs(parm->info);
	if (!parm->info->mutexs)
		return (-1);
	return (0);
}
