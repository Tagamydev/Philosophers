/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:51:42 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:51:56 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static useconds_t	get_actual_time_for_sleep(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_usleep(useconds_t usec)
{
	useconds_t		before;
	useconds_t		after;

	before = get_actual_time_for_sleep();
	after = before;
	while (after - before < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = get_actual_time_for_sleep();
	}
	return (0);
}

void	ft_sleep(t_philo *philo, unsigned int id)
{
	pthread_mutex_lock(philo->m_philo_printer);
	if (!is_dead(philo, id))
		printf("%u %u is sleeping\n", get_actual_time(philo), id + 1);
	pthread_mutex_unlock(philo->m_philo_printer);
	ft_usleep(philo->time_2_sleep);
}