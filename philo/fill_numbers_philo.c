/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_numbers_philo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:42:53 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:43:25 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	fill_numbers_philo(t_philo *philo, char **argv, size_t i)
{
	if (!philo || !*argv)
		return ;
	if (!i)
		philo->number_of_philos = ft_atoui(argv[i]);
	else if (i == 2)
		philo->time_2_eat = ft_atoui(argv[i]);
	else if (i == 3)
		philo->time_2_sleep = ft_atoui(argv[i]);
	else if (i == 1)
		philo->time_2_die = ft_atoui(argv[i]);
	else if (i == 4)
		philo->number_of_meals = ft_atoui(argv[i]);
}
