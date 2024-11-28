/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:13:57 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/28 15:58:22 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_is_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
		{
			if (str[i] == '-')
				error_massege("Error parsing", 0);
			else if (i == 0 && str[i] == '+')
			{
				i++;
				continue ;
			}
			else
				error_massege("Error parsing", 0);
			return (-1);
		}
	}
	return (0);
}

int	parsing(int ac, char **arg)
{
	int	i;
	int	is_error;

	i = 1;
	while (i < ac)
	{
		is_error = check_is_char(arg[i]);
		if (is_error == -1)
			return (-1);
		i++;
	}
	return (0);
}
