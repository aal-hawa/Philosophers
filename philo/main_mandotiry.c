/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandotiry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:08:49 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/10 13:20:18 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_info(t_info *info)
{
	
}

void	init_parm(t_parm *parm)
{
	
}

int	main(int ac, char **arg)
{
	t_info info;
	t_parm parm;
	
	if (ac != 4 || ac != 5)
		exit (1);
	init_info(&info);
	init_parm(&parm);
	parsing(&info);
	threads(&parm);
}