/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:13:01 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/12 18:00:27 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat(t_philo *philo, unsigned int id)
{
	lock_forks(philo, id);
	ft_usleep(philo->time_2_eat);
	unlock_forks(philo, id);
}
