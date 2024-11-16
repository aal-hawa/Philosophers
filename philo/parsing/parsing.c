/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:13:57 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/16 12:33:35 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	 parsing(int ac, char **arg)
{
	int	i;
	int	is_error;
	// only numbers
	// only possitive
	i = 0;
	while (i < ac)
	{
		is_error = check_is_char(arg[i]);
		if (is_error == -1)
			return (-1);
		i++;
	}
	// no zero philo
	// max int
	// up than 60
	return (0);
}
