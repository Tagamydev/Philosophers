/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:45:30 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 16:01:19 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	array_save(t_philo *philo)
{
	philo->p_philo_status = \
	malloc(sizeof(char) * (philo->number_of_philos + 1));
	if (!philo->p_philo_status)
		return (free_all_save(philo));
	philo->p_philo_status[philo->number_of_philos] = '\0';
	philo->p_philo_death = \
	malloc(sizeof(unsigned int) * (philo->number_of_philos));
	if (!philo->p_philo_death)
		return (free_all_save(philo));
	philo->p_philo_meals = \
	malloc(sizeof(unsigned int) * (philo->number_of_philos));
	if (!philo->p_philo_meals)
		return (free_all_save(philo));
	return (0);
}
