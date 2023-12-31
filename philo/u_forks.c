/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:13:36 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/12 17:28:41 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	unlock_fork(t_philo *philo, unsigned int id)
{
	pthread_mutex_unlock(philo->m_philo_forks + id);
}

static void	unlock_next_fork(t_philo *philo, unsigned int id)
{
	unsigned int	fork;

	fork = id + 1;
	if (fork < philo->number_of_philos)
		pthread_mutex_unlock(philo->m_philo_forks + fork);
	else
		pthread_mutex_unlock(philo->m_philo_forks + 0);
}

void	unlock_forks(t_philo *philo, unsigned int id)
{
	unlock_fork(philo, id);
	unlock_next_fork(philo, id);
}
