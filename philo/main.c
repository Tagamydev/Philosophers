/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:21:54 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:38:36 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

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
	start_sim(&philo);
	free_all(&philo);
	return (0);
}
