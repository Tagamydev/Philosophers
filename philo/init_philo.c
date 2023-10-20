/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:46:04 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:46:19 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_philo(t_philo *philo)
{
	philo->m_philo_status = NULL;
	philo->m_philo_forks = NULL;
	philo->m_philo_printer = NULL;
	philo->p_philo_status = NULL;
	philo->p_philo_death = NULL;
	philo->p_philo_meals = NULL;
	philo->number_of_philos = 0;
	philo->time_2_eat = 0;
	philo->time_2_sleep = 0;
	philo->time_2_die = 0;
	philo->number_of_meals = 0;
	philo->time_start = 0;
	philo->end = no;
}
