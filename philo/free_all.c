/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:42:07 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:42:24 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	free_all(t_philo *philo)
{
	m_free(philo->number_of_philos, philo->m_philo_status);
	philo->m_philo_status = NULL;
	m_free(philo->number_of_philos, philo->m_philo_death);
	philo->m_philo_death = NULL;
	m_free(philo->number_of_philos, philo->m_philo_forks);
	philo->m_philo_forks = NULL;
	m_free(1, philo->m_philo_printer);
	philo->m_philo_printer = NULL;
	m_free(1, philo->m_philo_loop);
	philo->m_philo_loop = NULL;
	m_free(1, philo->m_philo_id);
	philo->m_philo_id = NULL;
	free(philo->p_philo_status);
	philo->p_philo_status = NULL;
	free(philo->p_philo_death);
	philo->p_philo_death = NULL;
	free(philo->p_philo_meals);
	philo->p_philo_meals = NULL;
}
