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

void	ft_sleep(t_philo *philo, unsigned int id)
{
	pthread_mutex_lock(philo->m_philo_printer);
	if (!is_dead(philo))
		printf("%u %u is sleeping\n", get_actual_time(philo), id + 1);
	pthread_mutex_unlock(philo->m_philo_printer);
	pthread_mutex_lock(philo->m_philo_status + id);
	philo->p_philo_status[id] = SLEEPING;
	pthread_mutex_unlock(philo->m_philo_status + id);
	usleep(philo->time_2_sleep * 1000);
}
