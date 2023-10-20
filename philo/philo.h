/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:21:36 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/20 13:24:00 by samusanc         ###   ########.fr       */
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
# define DEAD 1
# define THINKING 2
# define EATING 3
# define SLEEPING 4

typedef enum e_bool{
	no = 0,
	yes = 1
}			t_bool;

typedef struct s_philo{
	pthread_mutex_t	*m_philo_status;
	pthread_mutex_t	*m_philo_forks;
	pthread_mutex_t	*m_philo_printer;
	pthread_mutex_t	*m_philo_loop;
	pthread_mutex_t	*m_philo_id;
	char			*p_philo_status;
	unsigned int	*p_philo_death;
	unsigned int	*p_philo_meals;
	unsigned int	number_of_philos;
	unsigned int	time_2_eat;
	unsigned int	time_2_sleep;
	unsigned int	time_2_die;
	unsigned int	number_of_meals;
	unsigned int	time_start;
	unsigned int	id;
	t_bool			limit_meals;
	t_bool			end;
}				t_philo;

int				ft_usleep(useconds_t usec);
void			lock_forks(t_philo *philo, unsigned int id);
void			unlock_forks(t_philo *philo, unsigned int id);
unsigned int	ft_atoui(char *nptr);
void			m_free(size_t len, pthread_mutex_t *mut);
void			free_all(t_philo *philo);
void			fill_numbers_philo(t_philo *philo, char **argv, size_t i);
pthread_mutex_t	*m_alloc_and_init(size_t len);
int				free_all_save(t_philo *philo);
int				mutex_save(t_philo *philo);
int				array_save(t_philo *philo);
void			init_philo(t_philo *philo);
unsigned int	ft_get_time_mili(void);
int				philo_parsing(t_philo *philo, char **argv);
unsigned int	get_actual_time(t_philo *philo);
int				is_dead(t_philo *philo, unsigned int id);
void			eat(t_philo *philo, unsigned int id);
void			is_philo_fat(t_philo *philo);
int				is_fat(t_philo *philo);
void			*ft_death(void *ptr);
void			ft_sleep(t_philo *philo, unsigned int id);
void			think(t_philo *philo, unsigned int id);
int				init_routine(t_philo *philo);
void			*routine(void *ptr);
int				start_sim(t_philo *philo);

#endif
