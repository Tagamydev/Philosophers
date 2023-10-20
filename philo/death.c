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

int	is_dead_loop(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philo->m_philo_loop);
	if (philo->end == no)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock(philo->m_philo_loop);
	return (i);
}

void	*ft_death(void *ptr)
{
	t_philo			*philo;
	unsigned int	i;

	philo = (t_philo *)ptr;
	usleep((philo->time_2_die * 1000));
	i = 0;
	while (!is_dead_loop(philo))
	{
		i = 0;
		while (i < philo->number_of_philos)
		{
			if (philo->limit_meals == yes)
				is_philo_fat(philo);
			i++;
		}
		usleep(philo->time_2_die / 2);
	}
	return (NULL);
}
