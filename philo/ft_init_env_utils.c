/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:43:24 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/30 21:11:53 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

unsigned int	ft_atou(const char *nptr)
{
	char				*str;
	unsigned int		r;
	int					s;

	str = (char *)nptr;
	r = 0;
	s = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 45)
		s = -s;
	if (*str == 45 || *str == 43)
		str++;
	while (*str >= 48 && *str <= 57)
		r = (r * 10) + (*str++ - '0');
	return (r);
}

void	ft_parse_env(t_env *env, int meals, char **numbers)
{	
	env->total_philo = ft_atou(numbers[0]);
	env->time_to_die = ft_atou(numbers[1]);
	env->time_to_eat = ft_atou(numbers[2]);
	env->time_to_sleep = ft_atou(numbers[3]);
	if (meals)
		env->number_of_meals = ft_atou(numbers[4]);
	env->starting_time = 0;
}

int	ft_init_mutex_env(t_env *env)
{
	env->printer = malloc(sizeof(pthread_mutex_t));
	if (!env->printer)
		return (0);
	if (pthread_mutex_init(env->printer, NULL))
		return (0);
	env->speed_force = malloc(sizeof(pthread_mutex_t));
	if (!env->speed_force)
		return (0);
	if (pthread_mutex_init(env->speed_force, NULL))
		return (0);
	env->agora = malloc(sizeof(pthread_t) * env->total_philo);
	if (!env->agora)
		return (0);
	return (1);
}

int	ft_fill_new_philo(t_philo *philo, t_env *env, unsigned int i)
{
	philo->philo_number = i;
	philo->number_of_meals = 0;
	philo->hungry = true;
	philo->eating = false;
	philo->time_to_die = 0;
	philo->block_philo = malloc(sizeof(pthread_mutex_t));
	if (!philo->block_philo)
		return (0);
	if (pthread_mutex_init(philo->block_philo, NULL))
		return (0);
	philo->own_fork = env->forks + i;
	if (i <= env->total_philo - 1)
		philo->other_fork = env->forks + (i + 1);
	else
		philo->other_fork = env->forks;
	philo->env = env;
	return (1);
}
