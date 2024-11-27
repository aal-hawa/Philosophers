/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:57:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/27 19:23:41 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// int	get_cur_time_millscd(t_info *info)
// {
// 	struct timeval	cur_time;
// 	long			curr_time_sec;
// 	long			curr_time_microsec;
// 	int				curr_time_millsecond;

// 	gettimeofday(&cur_time, NULL);
// 	curr_time_sec = cur_time.tv_sec - info->fst_time.tv_sec;
// 	curr_time_microsec = cur_time.tv_usec - info->fst_time.tv_usec;
// 	curr_time_millsecond = (int)((curr_time_sec * 1000)
// 			+ (curr_time_microsec / 1000));
// 	return (curr_time_millsecond);
// }

int	get_cur_time_millscd(t_info *info)
{
	gettimeofday(&info->cur_time, NULL);
	return ((long)((info->cur_time.tv_sec - info->fst_time.tv_sec) * 1000)
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
