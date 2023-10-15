/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:53:42 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:53:58 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

unsigned int	ft_get_time_mili(void)
{
	unsigned int		time;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (time);
}

unsigned int	get_actual_time(t_philo *philo)
{
	return (ft_get_time_mili() - philo->time_start);
}
