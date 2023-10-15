/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:39:57 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 16:04:08 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	start_sim_error(pthread_t *philos)
{
	free(philos);
	return (-1);
}

int	start_sim(t_philo *philo)
{
	pthread_t		*philos;
	pthread_t		death;
	unsigned int	i;

	i = 0;
	philos = malloc(sizeof(pthread_t) * (philo->number_of_philos + 1));
	if (!philos)
		return (start_sim_error(philos));
	if (pthread_create(&death, NULL, &ft_death, (void *)philo))
		return (start_sim_error(philos));
	while (i < philo->number_of_philos)
	{
		if (pthread_create(philos + i++, NULL, &routine, (void *)philo))
			return (1);
	}
	pthread_join(death, NULL);
	i = 0;
	while (i < philo->number_of_philos)
	{
		if (pthread_join(philos[i++], NULL))
			return (1);
	}
	free(philos);
	return (0);
}
