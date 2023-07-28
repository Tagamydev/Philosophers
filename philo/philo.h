/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:21:36 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/28 20:57:46 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# define FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define EAT "is eating"
# define DEAD "died"

typedef struct s_philo{
	pthread_mutex_t	*id;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*counter_incrementer;
	unsigned int	counter;
	int				alive;
	unsigned int		*last_meals;
	unsigned int	*number_meals;
}				t_philo;

typedef struct s_env{
	pthread_mutex_t	*forks;
	unsigned int	total_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_meals;
	t_philo			*philo;
}				t_env;

void			*ft_free(void **str);
int				ft_fill_arrays(t_env *env);
void			*ft_free_philo(t_philo *philo);
void			ft_fill_meals(unsigned int *meals, unsigned int total);
void			*ft_free_env(t_env *env);
unsigned int	ft_atoi(const char *nptr);
void			ft_parse_env(t_env *env, int meals, char **numbers);
t_env			*ft_init_env(char **numbers, int meals);
int				main(int argc, char **argv);

#endif
