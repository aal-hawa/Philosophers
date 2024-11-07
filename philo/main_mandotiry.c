/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandotiry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:08:49 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/07 13:50:04 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_info(t_info *info)
{
	
}

int	main(int ac, char **arg)
{
	t_info info;
	
	if (ac != 4 || ac != 5)
		exit (1);
	init_info(&info);
	parsing(&info);
	threads(&info);
}