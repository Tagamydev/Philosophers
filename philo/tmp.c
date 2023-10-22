/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:35:47 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:58:32 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	philo_parsing(t_philo *philo, char **argv)
{
	size_t	i;

	i = 0;
	if (!philo)
		return (-1);
	init_philo(philo);
	philo->id = 0;
	while (argv[i])
		fill_numbers_philo(philo, argv, i++);
	if (!philo->number_of_philos || !philo->time_2_die \
	|| (philo->limit_meals && !philo->number_of_meals))
		return (-1);
	if (mutex_save(philo))
		return (-1);
	if (array_save(philo))
		return (-1);
	philo->time_start = ft_get_time_mili();
	return (0);
}

int	is_dead(t_philo *philo, unsigned int id)
{
	int				i;

	i = 0;
	id = 0;
	pthread_mutex_lock(philo->m_philo_loop);
	if (philo->end == yes)
	{
		pthread_mutex_unlock(philo->m_philo_loop);
		return (1);
	}
	pthread_mutex_unlock(philo->m_philo_loop);
	return (i);
}

void	think(t_philo *philo, unsigned int id)
{
	pthread_mutex_lock(philo->m_philo_printer);
	if (!is_dead(philo, id))
		printf("%u %u is thinking\n", get_actual_time(philo), id + 1);
	pthread_mutex_unlock(philo->m_philo_printer);
}
