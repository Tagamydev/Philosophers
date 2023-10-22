/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:50:41 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/22 17:50:58 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_fat(t_fat *fat, t_philo *philo)
{
	fat->i = 0;
	fat->j = 0;
	fat->k = 0;
	fat->time = get_actual_time(philo);
}

int	is_fat(t_philo *philo)
{
	t_fat	fat;

	init_fat(&fat, philo);
	while (fat.i < philo->number_of_philos)
	{
		pthread_mutex_lock(philo->m_philo_status + fat.i);
		if (philo->p_philo_meals[fat.i] >= philo->number_of_meals)
			fat.j += 1;
		if (fat.time > philo->p_philo_death[fat.i])
		{
			fat.k = 1;
			pthread_mutex_lock(philo->m_philo_loop);
			if (philo->end == no)
				printf("%u %u is dead\n", fat.time, fat.i + 1);
			philo->end = yes;
			pthread_mutex_unlock(philo->m_philo_loop);
		}
		pthread_mutex_unlock(philo->m_philo_status + fat.i);
		fat.i += 1;
	}
	if ((philo->limit_meals == yes && \
	fat.j == philo->number_of_philos) || fat.k)
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
			is_philo_fat(philo);
			i++;
		}
	}
	return (NULL);
}
