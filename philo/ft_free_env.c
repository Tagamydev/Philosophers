/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:42:14 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/30 21:49:53 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

void	ft_free_philos(void *ptr)
{
	t_philo			*philo_tmp;

	if (!ptr)
		return ;
	philo_tmp = (t_philo *)ptr;
	pthread_mutex_destroy(philo_tmp->block_philo);
	ft_free((void **)&philo_tmp->block_philo);
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
	i = 0;
	while (i != env->total_philo)
		pthread_detach(env->agora[i++]);
	free(env->agora);
	i = 0;
	while (i != env->total_philo)
		pthread_mutex_destroy(env->forks + i++);
	ft_free((void **)&env->forks);
	i = 0;
	while (i != env->total_philo)
		pthread_mutex_destroy(env->philos[i++].block_philo);
	ft_free((void **)&env->philos);
	ft_free((void **)&env);
	return (NULL);
}
