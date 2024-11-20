/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandotiry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:08:49 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/20 13:21:11 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(t_info *info,int ac, char **arg)
{
	int is_error;
	
	is_error = 0;
	info->philo_count = ft_atoi(arg[1]);
	if (info->philo_count == 0)
		is_error = error_massege("Error no philo", is_error);
	info->to_die = ft_atoi(arg[2]);
	if (info->to_die == 0)
		is_error = error_massege("Error no philo", is_error);
	info->to_eat = ft_atoi(arg[3]);
	if (info->to_eat == 0)
		is_error = error_massege("Error no philo", is_error);
	info->to_sleep = ft_atoi(arg[4]);
	if (info->to_sleep == 0)
		is_error = error_massege("Error no philo", is_error);
	if (ac == 6)
	{
		info->how_many_eat = ft_atoi(arg[5]);
		if (info->how_many_eat == 0)
			is_error = error_massege("Error no philo", is_error);
	}
	else
		info->how_many_eat = 0;
	info->last_philo_got_it = 1;
	info->is_get_timer = 0;
	return (is_error);	
}

// void	init_parm(t_parm *parm)
// {
	
// }
void	free_all_mlc(t_parm *parm)
{
	exit(0);
	// pthread_detach();
	free(parm->pthrd);
}

int	main(int ac, char **arg)
{
	t_info info;
	t_parm parm;
	int	is_error;
	if (ac < 5 || ac > 6)
	{
		error_massege("Error four or five paramiter", 0);
		exit (1);
	}
	is_error = parsing(ac, arg);
	if (is_error == -1)
		exit (1);
	info.last_philo_got_it = 1;
	is_error = init_info(&info, ac, arg);
	if (is_error == -1)
		exit (1);
	// init_parm(&parm);
	parm.info = &info;
	is_error = threads(&parm);
	
	if (is_error == -2)
		exit (1);
	free_all_mlc(&parm);
}