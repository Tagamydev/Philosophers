/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simcity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:32:19 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/30 17:11:32 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

int	ft_print_room(t_env *env, int x, char *menssage)
{
	unsigned int		time;
	t_philo			*philo;

	philo = env->philo;
	pthread_mutex_lock(philo->printer);
	time = ft_get_time_mili() - env->start_time;
	if (philo->alive)
		printf("%u %d %s\n", time, x, menssage);
	pthread_mutex_unlock(philo->printer);
	return (1);
}

int	ft_eat(t_env *env, unsigned int philo_number)
{
	ft_lock_forks(env, philo_number);
	pthread_mutex_lock(&env->philo->id[philo_number]);
	env->philo->number_meals[philo_number] += 1;
	ft_put_last_meal(env, philo_number);
	ft_print_room(env, philo_number, EAT);
	usleep(env->time_to_eat * 1000);
	pthread_mutex_unlock(&env->philo->id[philo_number]);
	ft_unlock_forks(env, philo_number);
	return (0);
}

void	ft_put_last_meal(t_env	*env, unsigned int philo_number)
{
	t_philo				*philo;
	unsigned int		time;

	philo = env->philo;
	time = ft_get_time_mili();
	philo->last_meals[philo_number] = time;
}

void	ft_unlock_forks(t_env *env, unsigned int philo_number)
{
	ft_unlock_fork(env, philo_number);
	ft_unlock_next_fork(env, philo_number);
	ft_print_room(env, philo_number, SLEEP);
	usleep((env->time_to_sleep) * 1000);
}

void	ft_lock_forks(t_env *env, unsigned int philo_number)
{
	ft_lock_fork(env, philo_number);
	ft_lock_next_fork(env, philo_number);
}

void	ft_unlock_next_fork(t_env *env, unsigned int philo_number)
{
	unsigned int	i;

	i = 0;
	if (philo_number == env->total_philo)
		i = 0;
	else
		i = philo_number + 1;
	pthread_mutex_unlock(&env->forks[i]);
}

void	ft_unlock_fork(t_env *env, unsigned int philo_number)
{
	pthread_mutex_unlock(&env->forks[philo_number]);
}

void	ft_lock_next_fork(t_env *env, unsigned int philo_number)
{
	unsigned int	i;

	i = 0;
	if (philo_number == env->total_philo)
		i = 0;
	else
		i = philo_number + 1;
	pthread_mutex_lock(&env->forks[i]);
	ft_print_room(env, philo_number, FORK);
}

void	ft_lock_fork(t_env *env, unsigned int philo_number)
{
	pthread_mutex_lock(&env->forks[philo_number]);
	ft_print_room(env, philo_number, FORK);
}
