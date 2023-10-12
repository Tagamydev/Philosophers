/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:13:01 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/12 17:57:10 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat(t_philo *philo, unsigned int id)
{
	lock_forks(philo, id);
	pthread_mutex_lock(philo->m_philo_printer);
	if (philo->end == no)
		printf("%u %u is eating\n", get_actual_time(philo), id + 1);
	pthread_mutex_unlock(philo->m_philo_printer);
	pthread_mutex_lock(philo->m_philo_death + id);
	philo->p_philo_death[id] = get_actual_time(philo) + philo->time_2_die;
	pthread_mutex_unlock(philo->m_philo_death + id);
	pthread_mutex_lock(philo->m_philo_status + id);
	philo->p_philo_status[id] = EATING;
	philo->p_philo_meals[id] += 1;
	pthread_mutex_unlock(philo->m_philo_status + id);
	usleep(philo->time_2_eat * 1000);
	unlock_forks(philo, id);
}
