/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:14:04 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/30 21:01:00 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

int	ft_init_philos_env(t_env *env)
{
	t_philo			*philos;
	unsigned int	total;
	unsigned int	i;

	total = env->total_philo;
	i = 0;
	philos = malloc(sizeof(t_philo) * total);
	if (!philos)
		return (0);
	while (i < total)
	{
		if (!ft_fill_new_philo(philos + i, env, i))
			return (0);
		i++;
	}
	env->philos = philos;
	return (1);
}

int	ft_init_forks_env(t_env *env)
{
	unsigned int	total;
	unsigned int	i;
	pthread_mutex_t	*forks;

	total = env->total_philo;
	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * total);
	if (!forks)
		return (0);
	while (i != total)
	{
		if (pthread_mutex_init(forks + i++, NULL))
			return (0);
	}
	env->forks = forks;
	return (1);
}

t_env	*ft_init_env(char **numbers, int meals)
{
	t_env			*env;

	env = NULL;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	ft_parse_env(env, meals, numbers);
	if (!ft_init_mutex_env(env))
		return ((t_env *)ft_free_env(env));
	if (!ft_init_forks_env(env))
		return ((t_env *)ft_free_env(env));
	if (!ft_init_philos_env(env))
		return ((t_env *)ft_free_env(env));
	return (env);
}

#if 0
int	ft_fill_arrays(t_env *env)
{
	pthread_mutex_t *forks;
	pthread_mutex_t *id;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * env->total_philo);
	if (!forks)
		return (1);
	id = malloc(sizeof(pthread_mutex_t) * env->total_philo);
	if (!id)
	{
		free(forks);
		return (1);
	}
	i = 0;
	while (i  != env->total_philo)
		pthread_mutex_init(forks + i++, NULL);
	env->forks = forks;
	i = 0;
	while (i  != env->total_philo)
		pthread_mutex_init(id + i++, NULL);
	env->philo->id = id;
	return (0);
}

void	*ft_free_philo(t_philo *philo)
{
	if (!philo)
		return (NULL);
	ft_free((void **)&philo->id);
	ft_free((void **)&philo->printer);
	ft_free((void **)&philo->counter_incrementer);
	ft_free((void **)&philo->last_meals);
	ft_free((void **)&philo->number_meals);
	return (NULL);
}

void	ft_fill_meals(unsigned int *meals, unsigned int total)
{
	unsigned int	i;

	i = 0;
	while (i != total)
		meals[i++] = 0;
}

t_philo	*ft_init_philo(unsigned int total_philo)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = NULL;
	philo->printer = NULL;
	philo->counter_incrementer = NULL;
	philo->last_meals = 0;
	philo->counter_incrementer = malloc(sizeof(pthread_mutex_t));
	if (!philo->counter_incrementer)
		return ((t_philo *)ft_free_philo(philo));
	pthread_mutex_init(philo->counter_incrementer, NULL);
	philo->printer = malloc(sizeof(pthread_mutex_t));
	if (!philo->printer)
		return ((t_philo *)ft_free_philo(philo));
	pthread_mutex_init(philo->printer, NULL);
	philo->last_meals = malloc(total_philo * sizeof(unsigned int));
	if (!philo->last_meals)
		return ((t_philo *)ft_free_philo(philo));
	philo->number_meals = malloc(total_philo * sizeof(unsigned int));
	if (!philo->number_meals)
		return ((t_philo *)ft_free_philo(philo));
	ft_fill_meals(philo->last_meals, total_philo);
	ft_fill_meals(philo->number_meals, total_philo);
	return (philo);
}

void	*ft_free_env(t_env *env)
{
	if (!env)
		return (NULL);
	ft_free((void **)&env->forks);
	return ((t_philo *)ft_free_philo(env->philo));
}

unsigned int	ft_atoi(const char *nptr)
{
	char	*str;
	unsigned int		r;
	int		s;

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
	env->total_philo = ft_atoi(numbers[0]);
	env->time_to_die = ft_atoi(numbers[1]);
	env->time_to_sleep = ft_atoi(numbers[3]);
	env->time_to_eat = ft_atoi(numbers[2]);
	if (meals)
		env->number_of_meals = ft_atoi(numbers[4]);
	numbers = NULL;
}

t_env	*ft_init_env(char **numbers, int meals)
{
	t_env			*env;
	t_philo			*philo;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	ft_parse_env(env, meals, numbers);
	env->forks = NULL;
	philo = ft_init_philo(env->total_philo);
	if (!philo)
		return ((t_env *)ft_free((void **)&env));
	env->philo = philo;
	if (ft_fill_arrays(env))
		return ((t_env *)ft_free_env(env));
	philo->counter = 0;
	philo->alive = 1;
	return (env);
}

#endif



