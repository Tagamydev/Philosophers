/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:44:32 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:45:00 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	free_all_save(t_philo *philo)
{
	free_all(philo);
	return (-1);
}

int	mutex_save(t_philo *philo)
{
	philo->m_philo_status = m_alloc_and_init(philo->number_of_philos);
	if (!philo->m_philo_status)
		return (free_all_save(philo));
	philo->m_philo_death = m_alloc_and_init(philo->number_of_philos);
	if (!philo->m_philo_death)
		return (free_all_save(philo));
	philo->m_philo_forks = m_alloc_and_init(philo->number_of_philos);
	if (!philo->m_philo_forks)
		return (free_all_save(philo));
	philo->m_philo_printer = m_alloc_and_init(1);
	if (!philo->m_philo_printer)
		return (free_all_save(philo));
	philo->m_philo_id = m_alloc_and_init(1);
	if (!philo->m_philo_id)
		return (free_all_save(philo));
	philo->m_philo_loop = m_alloc_and_init(1);
	if (!philo->m_philo_loop)
		return (free_all_save(philo));
	return (0);
}
