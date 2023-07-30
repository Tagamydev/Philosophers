/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:21:36 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/30 22:13:59 by samusanc         ###   ########.fr       */
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

typedef enum e_bool{
	false = 0,
	true = 1
}				t_bool;

struct s_philo;

typedef struct s_env{
	pthread_t		*agora;
	unsigned int	total_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_meals;
	unsigned int	starting_time;
	t_bool			alive;
	t_bool			fat;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*speed_force;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}				t_env;

typedef struct s_philo{
	pthread_t		*shinigami;
	unsigned int	philo_number;
	unsigned int	number_of_meals;
	t_bool			hungry;
	t_bool			eating;
	unsigned int	time_to_die;
	pthread_mutex_t	*block_philo;
	pthread_mutex_t	*own_fork;
	pthread_mutex_t	*other_fork;
	t_env			*env;
}				t_philo;

unsigned int	ft_get_time_mili(void);
void			*ft_free(void **str);
unsigned int	ft_atou(const char *nptr);
void			ft_free_philos(void *ptr);
void			*ft_free_env(t_env *env);
void			ft_parse_env(t_env *env, int meals, char **numbers);
int				ft_init_mutex_env(t_env *env);
int				ft_fill_new_philo(t_philo *philo, t_env *env, unsigned int i);
int				ft_init_philos_env(t_env *env);
int				ft_init_forks_env(t_env *env);
t_env			*ft_init_env(char **numbers, int meals);

/*
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
	unsigned int	start_time;
	t_philo			*philo;
}				t_env;

typedef struct s_sheriff{
	unsigned int	philo_number;
	t_env			*env;
}				t_sheriff;

void			ft_put_last_meal(t_env *env, unsigned int philo_number);
int				ft_print_room(t_env *env, int x, char *menssage);
unsigned int	ft_get_time_mili(void);
//			FORKS
void			ft_unlock_next_fork(t_env *env, unsigned int philo_number);
void			ft_unlock_fork(t_env *env, unsigned int philo_number);
void			ft_lock_next_fork(t_env *env, unsigned int philo_number);
void			ft_lock_fork(t_env *env, unsigned int philo_number);
void			ft_lock_forks(t_env *env, unsigned int philo_number);
void			ft_unlock_forks(t_env *env, unsigned int philo_number);
int				ft_eat(t_env *env, unsigned int philo_number);

void			*ft_free(void **str);
int				ft_fill_arrays(t_env *env);
void			*ft_free_philo(t_philo *philo);
void			ft_fill_meals(unsigned int *meals, unsigned int total);
void			*ft_free_env(t_env *env);
unsigned int	ft_atoi(const char *nptr);
void			ft_parse_env(t_env *env, int meals, char **numbers);
t_env			*ft_init_env(char **numbers, int meals);
int				main(int argc, char **argv);
*/

#endif
