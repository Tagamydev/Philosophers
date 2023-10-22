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
	if (!is_dead(philo, id))
		printf("%u %u has taken a fork\n", get_actual_time(philo), id + 1);
	pthread_mutex_unlock(philo->m_philo_printer);
}

static void	take_forks(t_philo *philo, unsigned int id)
{
	unsigned int	actual_time;

	actual_time = get_actual_time(philo);
	printf("%u %u has taken a fork\n", actual_time, id + 1);
	printf("%u %u is eating\n", actual_time, id + 1);
	pthread_mutex_lock(philo->m_philo_status + id);
	if (philo->limit_meals == yes)
		philo->p_philo_meals[id] += 1;
	philo->p_philo_death[id] = actual_time + philo->time_2_die;
	pthread_mutex_unlock(philo->m_philo_status + id);
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
	if (!is_dead(philo, id))
		take_forks(philo, id);
	pthread_mutex_unlock(philo->m_philo_printer);
}

void	lock_forks(t_philo *philo, unsigned int id)
{
	lock_fork(philo, id);
	lock_next_fork(philo, id);
}
