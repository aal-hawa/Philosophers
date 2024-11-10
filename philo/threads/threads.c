/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:25:10 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/10 15:11:16 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *do_threed_philpo(t_parm *parm)
{
	
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
	while (i < parm->info->philo_count)
	{
		pthread_join(p[i], NULL);
		i++;
	}
	return (0);
}
