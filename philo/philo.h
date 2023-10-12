/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:21:36 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/12 18:28:21 by samusanc         ###   ########.fr       */
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
	pthread_mutex_t	*m_philo_status;//status of each philo (MUTEX)
	//el mutex del status se va a utilizar para actalizar el status y el number of meals
	pthread_mutex_t	*m_philo_death;//time of death of each philo (MUTEX)
	pthread_mutex_t	*m_philo_forks;//the forks of each philo (MUTEX)
	pthread_mutex_t	*m_philo_printer;//the only printer for the entire philo (MUTEX)
	pthread_mutex_t	*m_philo_loop;//the mutex for the loop (MUTEX)
	pthread_mutex_t	*m_philo_id;//the only printer for the entire philo (MUTEX)
	char			*p_philo_status;//status of each philo (VARIABLE)
	unsigned int	*p_philo_death;//time of death of each philo
	unsigned int	*p_philo_meals;//number of meals done by each philo
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
int				is_dead(t_philo *philo);
void			eat(t_philo *philo, unsigned int id);

#endif
