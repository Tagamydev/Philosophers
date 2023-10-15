/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:50:41 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 16:04:44 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	is_fat(t_philo *philo)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < philo->number_of_philos)
	{
		pthread_mutex_lock(philo->m_philo_status + i);
		if (philo->p_philo_meals[i] >= philo->number_of_meals)
			j++;
		pthread_mutex_unlock(philo->m_philo_status + i);
		i++;
	}
	if (j == philo->number_of_philos)
		return (1);
	return (0);
}

void	is_philo_fat(t_philo *philo)
{
	if (is_fat(philo))
	{
		pthread_mutex_lock(philo->m_philo_loop);
		philo->end = yes;
		pthread_mutex_unlock(philo->m_philo_loop);
	}
}

void	death_loop(t_philo *philo, unsigned int i)
{
	pthread_mutex_lock(philo->m_philo_status + i);
	if (philo->p_philo_status[i] != EATING)
	{
		pthread_mutex_lock(philo->m_philo_printer);
		if (!is_dead(philo))
			printf("%u %u died\n", get_actual_time(philo), i + 1);
		pthread_mutex_lock(philo->m_philo_loop);
		philo->end = yes;
		pthread_mutex_unlock(philo->m_philo_loop);
		pthread_mutex_unlock(philo->m_philo_printer);
	}
	pthread_mutex_unlock(philo->m_philo_status + i);
}

void	*ft_death(void *ptr)
{
	t_philo			*philo;
	unsigned int	i;

	philo = (t_philo *)ptr;
	usleep((philo->time_2_die * 1000));
	while (!is_dead(philo))
	{
		i = 0;
		while (i < philo->number_of_philos)
		{
			pthread_mutex_lock(philo->m_philo_death + i);
			if (get_actual_time(philo) > philo->p_philo_death[i])
				death_loop(philo, i);
			if (philo->limit_meals == yes)
				is_philo_fat(philo);
			pthread_mutex_unlock(philo->m_philo_death + i);
			i++;
		}
		usleep(philo->time_2_die / 2);
	}
	return (NULL);
}
