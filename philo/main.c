/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:21:54 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 17:47:28 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

int	one_philo(t_philo *philo)
{
	printf("%u 1 has taken a fork\n", get_actual_time(philo));
	usleep(philo->time_2_die * 1000);
	printf("%u 1 died\n", get_actual_time(philo));
	free_all(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: number_of_philosophers time_to_die time_to_eat"\
		" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (argc == 6)
		philo.limit_meals = yes;
	else
		philo.limit_meals = no;
	if (philo_parsing(&philo, ++argv))
		return (-1);
	if (philo.number_of_philos == 1)
		return (one_philo(&philo));
	start_sim(&philo);
	free_all(&philo);
	return (0);
}
