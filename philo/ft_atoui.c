/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:40:46 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:41:10 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

unsigned int	ft_atoui(char *nptr)
{
	char			*str;
	unsigned int	r;
	int				s;

	if (!nptr)
		return (0);
	str = (char *)nptr;
	r = 0;
	s = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 45)
		s = -s;
	if (*str == 45 || *str == 43)
		str++;
	while (*str >= 48 && *str <= 57)
		r = (r * 10) + (*str++ - '0');
	return ((unsigned int)r);
}
