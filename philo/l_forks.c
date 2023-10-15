/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_forks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:15:27 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 17:49:55 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	lock_fork(t_philo *philo, unsigned int id)
{
	pthread_mutex_lock(philo->m_philo_forks + id);
	pthread_mutex_lock(philo->m_philo_printer);
	if (philo->end == no)
		printf("%u %u has taken a fork\n", get_actual_time(philo), id + 1);
	pthread_mutex_unlock(philo->m_philo_printer);
}

static void	lock_next_fork(t_philo *philo, unsigned int id)
{
	unsigned int	fork;

	fork = id + 1;
	if (fork < philo->number_of_philos)
		pthread_mutex_lock(philo->m_philo_forks + fork);
	else
		pthread_mutex_lock(philo->m_philo_forks + 0);
	pthread_mutex_lock(philo->m_philo_printer);
	if (philo->end == no)
		printf("%u %u has taken a fork\n", get_actual_time(philo), id + 1);
	pthread_mutex_unlock(philo->m_philo_printer);
}

void	lock_forks(t_philo *philo, unsigned int id)
{
	lock_fork(philo, id);
	lock_next_fork(philo, id);
}
