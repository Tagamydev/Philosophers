/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:54:40 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 16:04:18 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	init_routine(t_philo *philo)
{
	unsigned int	id;

	id = 0;
	pthread_mutex_lock(philo->m_philo_id);
	id = philo->id++;
	philo->p_philo_death[id] = get_actual_time(philo) + philo->time_2_die;
	pthread_mutex_unlock(philo->m_philo_id);
	return (id);
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	unsigned int	id;

	id = 0;
	philo = (t_philo *)ptr;
	id = init_routine(philo);
	if (!(id % 2))
		usleep(300);
	while (!is_dead(philo, id))
	{
		eat(philo, id);
		ft_sleep(philo, id);
		think(philo, id);
	}
	return (NULL);
}
