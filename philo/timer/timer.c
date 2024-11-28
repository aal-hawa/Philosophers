/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:57:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/28 15:48:39 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_cur_time_millscd(t_info *info)
{
	gettimeofday(&info->cur_time, NULL);
	return ((int)((info->cur_time.tv_sec - info->fst_time.tv_sec) * 1000)
			+ ((info->cur_time.tv_usec - info->fst_time.tv_usec) / 1000));
}

void	get_first_time_millscd(t_info *info)
{
	if (info->is_get_timer == 0)
	{
		info->is_get_timer = 1;
		gettimeofday(&info->fst_time, NULL);
	}
}
