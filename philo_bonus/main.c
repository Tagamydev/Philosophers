/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:21:54 by samusanc          #+#    #+#             */
/*   Updated: 2023/09/25 21:04:47 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: number_of_philosophers time_to_die time_to_eat"\
		" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	printf("argc:%d\n", argc);
	return (0);
	argc = 0;
	argv = NULL;
}
