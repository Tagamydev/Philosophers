/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:21:36 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/25 21:48:36 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#define FORK "has taken a fork"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define EAT "is eating"
#define DEAD "died"

typedef struct s_philo{
	pthread_mutex_t	*id;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*counter_incrementer;
	unsigned int	counter;
	int				alive;
	long long		*last_meals;
}				t_philo;

typedef struct s_env{
	pthread_mutex_t	*forks;
	unsigned int	total_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	t_philo			*philo;
}				t_env;

#endif
