/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandotiry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:08:49 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/12/04 20:20:57 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res > 2147483647)
			return (0);
		i++;
	}
	res *= sign;
	return ((int)res);
}

static int	check_args(t_info *info, int ac, char **arg, int is_error)
{
	if (ac == 6)
	{
		info->how_many_eat = ft_atoi(arg[5]);
		if (info->how_many_eat == 0)
			is_error = error_massege("Error parsing", is_error);
	}
	else
		info->how_many_eat = 0;
	return (is_error);
}

static int	init_info(t_info *info, int ac, char **arg)
{
	int	is_error;

	is_error = 0;
	info->philo_count = ft_atoi(arg[1]);
	if (info->philo_count == 0 || info->philo_count > 200)
		is_error = error_massege("Error parsing", is_error);
	info->to_die = ft_atoi(arg[2]);
	if (info->to_die == 0)
		is_error = error_massege("Error parsing", is_error);
	info->to_eat = ft_atoi(arg[3]);
	if (info->to_eat == 0)
		is_error = error_massege("Error parsing", is_error);
	info->to_sleep = ft_atoi(arg[4]);
	if (info->to_sleep == 0)
		is_error = error_massege("Error parsing", is_error);
	is_error = check_args(info, ac, arg, is_error);
	info->last_philo_got_it = 1;
	info->is_get_timer = 0;
	info->is_died = 0;
	return (is_error);
}

int	main(int ac, char **arg)
{
	t_info	info;
	t_parm	parm;
	int		is_error;

	if (ac < 5 || ac > 6)
	{
		error_massege("Error parsing", 0);
		return (1);
	}
	is_error = parsing(ac, arg);
	if (is_error == -1)
		return (1);
	info.last_philo_got_it = 1;
	is_error = init_info(&info, ac, arg);
	if (is_error == -1)
		return (1);
	parm.info = &info;
	is_error = threads(&parm);
	free_all_mlc(&parm, is_error);
}
