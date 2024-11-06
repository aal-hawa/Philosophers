/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:56 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/11/06 16:32:11 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void	ft_putstr_fd(char *s, int fd, int is_malloc)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	if (is_malloc == 2 || is_malloc == -1)
		write(fd, "\n", 1);
	if (is_malloc == 1 || is_malloc == 2)
		free_char(s);
}