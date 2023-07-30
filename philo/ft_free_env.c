/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:42:14 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/30 20:22:34 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	ft_free_philos(t_philo *philos, unsigned int total)
{
	unsigned int	i;
	t_philo			*philo_tmp;

	i = 0;
	if (!philos)
		return ;
	while (i != total)
	{
		philo_tmp = philos + i++;
		pthread_mutex_destroy(philo_tmp->block_philo);
		ft_free((void **)&philo_tmp->block_philo);
	}
	ft_free((void **)&philos);
}

void	*ft_free_env(t_env *env)
{
	unsigned int	i;

	if (!env)
		return (NULL);
	pthread_mutex_destroy(env->printer);
	ft_free((void **)&env->printer);
	pthread_mutex_destroy(env->speed_force);
	ft_free((void **)&env->speed_force);
	ft_free_philos(env->philos, env->total_philo);
	i = 0;
	while (i != env->total_philo)
		pthread_mutex_destroy(env->forks + i++);
	ft_free((void **)&env->agora);
	ft_free((void **)&env->forks);
	ft_free((void **)&env);
	return (NULL);
}
