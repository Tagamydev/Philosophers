/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:21:54 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/12 18:57:32 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>


unsigned int	ft_atoui(char *nptr)
{
	char			*str;
	unsigned int	r;
	int				s;

	if (!nptr)
		return (0);
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
	return ((unsigned int)r);
}

void	m_free(size_t len, pthread_mutex_t *mut)
{
	size_t	i;

	i = 0;
	if (!mut)
		return ;
	while (i < len)
		pthread_mutex_destroy(mut + i++);
	free(mut);
}

void	free_all(t_philo *philo)
{
	m_free(philo->number_of_philos, philo->m_philo_status);
	philo->m_philo_status = NULL;
	m_free(philo->number_of_philos, philo->m_philo_death);
	philo->m_philo_death = NULL;
	m_free(philo->number_of_philos, philo->m_philo_forks);
	philo->m_philo_forks = NULL;
	m_free(1, philo->m_philo_printer);
	philo->m_philo_printer = NULL;
	m_free(1, philo->m_philo_loop);
	philo->m_philo_loop = NULL;
	m_free(1, philo->m_philo_id);
	philo->m_philo_id = NULL;
	free(philo->p_philo_status);
	philo->p_philo_status = NULL;
	free(philo->p_philo_death);
	philo->p_philo_death = NULL;
	free(philo->p_philo_meals);
	philo->p_philo_meals = NULL;
}

void	fill_numbers_philo(t_philo *philo, char **argv, size_t i)
{
	if (!philo || !*argv)
		return ;
	if (!i)
		philo->number_of_philos = ft_atoui(argv[i]);
	else if (i == 2)
		philo->time_2_eat = ft_atoui(argv[i]);
	else if (i == 3)
		philo->time_2_sleep = ft_atoui(argv[i]);
	else if (i == 1)
		philo->time_2_die = ft_atoui(argv[i]);
	else if (i == 4)
		philo->number_of_meals = ft_atoui(argv[i]);
}

pthread_mutex_t	*m_alloc_and_init(size_t len)
{
	pthread_mutex_t	*result;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	result = malloc(sizeof(pthread_mutex_t) * len);
	if (!result)
		return (NULL);
	while (i < len)
	{
		if (pthread_mutex_init(result + i, NULL))
		{
			while (j > i)
				pthread_mutex_destroy(result + j++);
			free(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}

int	free_all_save(t_philo *philo)
{
	free_all(philo);
	return (-1);
}

int	mutex_save(t_philo *philo)
{
	philo->m_philo_status = m_alloc_and_init(philo->number_of_philos);
	if (!philo->m_philo_status)
		return (free_all_save(philo));
	philo->m_philo_death = m_alloc_and_init(philo->number_of_philos);
	if (!philo->m_philo_death)
		return (free_all_save(philo));
	philo->m_philo_forks = m_alloc_and_init(philo->number_of_philos);
	if (!philo->m_philo_forks)
		return (free_all_save(philo));
	philo->m_philo_printer = m_alloc_and_init(1);
	if (!philo->m_philo_printer)
		return (free_all_save(philo));
	philo->m_philo_id = m_alloc_and_init(1);
	if (!philo->m_philo_id)
		return (free_all_save(philo));
	philo->m_philo_loop = m_alloc_and_init(1);
	if (!philo->m_philo_loop)
		return (free_all_save(philo));
	return (0);
}

int	array_save(t_philo *philo)
{
	philo->p_philo_status = malloc(sizeof(char) * (philo->number_of_philos + 1));
	if (!philo->p_philo_status)
		return (free_all_save(philo));
	philo->p_philo_status[philo->number_of_philos] = '\0';
	philo->p_philo_death = malloc(sizeof(unsigned int) * (philo->number_of_philos));
	if (!philo->p_philo_death)
		return (free_all_save(philo));
	philo->p_philo_meals = malloc(sizeof(unsigned int) * (philo->number_of_philos));
	if (!philo->p_philo_meals)
		return (free_all_save(philo));
	return (0);
}

void	init_philo(t_philo *philo)
{
	philo->m_philo_status = NULL;
	philo->m_philo_death = NULL;
	philo->m_philo_forks = NULL;
	philo->m_philo_printer = NULL;
	philo->p_philo_status = NULL;
	philo->p_philo_death = NULL;
	philo->p_philo_meals = NULL;
	philo->number_of_philos = 0;
	philo->time_2_eat = 0;
	philo->time_2_sleep = 0;
	philo->time_2_die = 0;
	philo->number_of_meals = 0;
	philo->time_start = 0;
	philo->end = no;
}

unsigned int	ft_get_time_mili(void)
{
	unsigned int		time;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (time);
}

int	philo_parsing(t_philo *philo, char **argv)
{
	size_t	i;

	i = 0;
	if (!philo)
		return (-1);
	init_philo(philo);
	philo->id = 0;
	while (argv[i])
		fill_numbers_philo(philo, argv, i++);
	if (!philo->number_of_philos || !philo->time_2_die \
	|| (philo->limit_meals && !philo->number_of_meals))
		return (-1);
	if (mutex_save(philo))
		return (-1);
	if (array_save(philo))
		return (-1);
	philo->time_start = ft_get_time_mili();
	return (0);
}

unsigned int	get_actual_time(t_philo *philo)
{
	return (ft_get_time_mili() - philo->time_start);
}

int	is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philo->m_philo_loop);
	if (philo->end == no)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock(philo->m_philo_loop);
	return (i);
}

int	is_fat(t_philo *philo)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < philo->number_of_philos)
	{
		pthread_mutex_lock(philo->m_philo_status + i);
		if (philo->p_philo_meals[i] >= philo->number_of_meals)
			j++;
		pthread_mutex_unlock(philo->m_philo_status + i);
		i++;
	}
	if (j == philo->number_of_philos)
		return (1);
	return (0);
}

void	*ft_death(void *ptr)
{
	t_philo			*philo;
	unsigned int	i;
	
	philo = (t_philo *)ptr;
	usleep((philo->time_2_die * 1000));
	while (!is_dead(philo))
	{
		i = 0;
		while (i < philo->number_of_philos)
		{
			pthread_mutex_lock(philo->m_philo_death + i);
			if (get_actual_time(philo) > philo->p_philo_death[i])
			{
////////////////////////////////////////////////////////////////////////////////
				pthread_mutex_lock(philo->m_philo_status + i);
				if (philo->p_philo_status[i] != EATING)
				{
					pthread_mutex_lock(philo->m_philo_printer);
					if (!is_dead(philo))
						printf("%u %u died\n", get_actual_time(philo), i + 1);
					pthread_mutex_lock(philo->m_philo_loop);
					philo->end = yes;
					pthread_mutex_unlock(philo->m_philo_loop);
					pthread_mutex_unlock(philo->m_philo_printer);
				}
				pthread_mutex_unlock(philo->m_philo_status + i);
////////////////////////////////////////////////////////////////////////////////
			}
			if (philo->limit_meals == yes)
			{
////////////////////////////////////////////////////////////////////////////////
				if (is_fat(philo))
				{
					pthread_mutex_lock(philo->m_philo_loop);
					philo->end = yes;
					pthread_mutex_unlock(philo->m_philo_loop);
				}
////////////////////////////////////////////////////////////////////////////////
			}
			pthread_mutex_unlock(philo->m_philo_death + i);
			i++;
		}
		usleep(philo->time_2_die/2);
	}
	return (NULL);
}

void	ft_sleep(t_philo *philo, unsigned int id)
{
	pthread_mutex_lock(philo->m_philo_printer);
	if (!is_dead(philo))
		printf("%u %u is sleeping\n", get_actual_time(philo), id + 1);
	pthread_mutex_unlock(philo->m_philo_printer);
	pthread_mutex_lock(philo->m_philo_status + id);
	philo->p_philo_status[id] = SLEEPING;
	pthread_mutex_unlock(philo->m_philo_status + id);
	usleep(philo->time_2_sleep * 1000);
}

void	think(t_philo *philo, unsigned int id)
{
	pthread_mutex_lock(philo->m_philo_printer);
	if (!is_dead(philo))
		printf("%u %u is thinking\n", get_actual_time(philo), id + 1);
	pthread_mutex_unlock(philo->m_philo_printer);
	pthread_mutex_lock(philo->m_philo_status + id);
	philo->p_philo_status[id] = THINKING;
	pthread_mutex_unlock(philo->m_philo_status + id);
}

int	init_routine(t_philo *philo)
{
	unsigned int	id;

	id = 0;
	pthread_mutex_lock(philo->m_philo_id);
	id = philo->id++;
	pthread_mutex_lock(philo->m_philo_death + id);
	philo->p_philo_death[id] = get_actual_time(philo) + philo->time_2_die;
	pthread_mutex_unlock(philo->m_philo_death + id);
	pthread_mutex_lock(philo->m_philo_status + id);
	philo->p_philo_status[id] = THINKING;
	pthread_mutex_unlock(philo->m_philo_status + id);
	pthread_mutex_unlock(philo->m_philo_id);
	return (id);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	unsigned int	id;
	
	id = 0;
	philo = (t_philo *)ptr;
	id = init_routine(philo);
	if (!(id % 2))
		usleep(100);
	while (!is_dead(philo))
	{
		eat(philo, id);
		ft_sleep(philo, id);
		think(philo, id);
	}
	return (NULL);
}

int	start_sim_error(pthread_t *philos)
{
	free(philos);
	return (-1);
}

int	start_sim(t_philo *philo)
{
	pthread_t		*philos;
	pthread_t		death;
	unsigned int	i;

	i = 0;
	philos = malloc(sizeof(pthread_t) * (philo->number_of_philos + 1));
	if (!philos)
		return (start_sim_error(philos));
	if(pthread_create(&death, NULL, &ft_death, (void *)philo))
		return (start_sim_error(philos));
	while (i < philo->number_of_philos)
	{
		if(pthread_create(philos + i, NULL, &routine, (void *)philo))
			return (1);
		++i;
	}
	if(pthread_join(death, NULL))
		return (1);
	i = 0;
	while (i < philo->number_of_philos)
	{
		if(pthread_join(philos[i], NULL))
			return (1);
		++i;
	}
	free(philos);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: number_of_philosophers time_to_die time_to_eat"\
		" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (argc == 6)
		philo.limit_meals = yes;
	else
		philo.limit_meals = no;
	if (philo_parsing(&philo, ++argv))
		return (-1);
	start_sim(&philo);
	free_all(&philo);
	return (0);
}
