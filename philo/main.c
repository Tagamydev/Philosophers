/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:21:54 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/24 21:31:05 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>


#if 1

long long	ft_get_time_mili(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (time);
}

int	ft_check_death(t_philo *philo, int philo_number)
{
	long long	time;

	time = ft_get_time_mili();
	pthread_mutex_lock(philo->death);
	if (!philo->alive)
	{
		pthread_mutex_unlock(philo->death);
		return (0);
	}
	if ((time - philo->last_meals[philo_number]) > philo->time_to_die)
	{
		philo->alive = 0;
		printf("%lld %d died\n", time, philo_number);
		pthread_mutex_unlock(philo->death);
		return (0);
	}
	pthread_mutex_unlock(philo->death);
	return (1);
}


int	ft_print_messaje(t_philo *philo, char type, int x)
{
	long long		time;

	if (!ft_check_death(philo, x))
		return (1);
	pthread_mutex_lock(philo->printer);
	time = ft_get_time_mili();
	if (philo->alive)
	{
		if (type == 'F')
			printf("%lld %d has taken a fork\n", time, x);
		else if (type == 'E')
			printf("%lld %d is eating\n", time, x);
		else if (type == 'S')
			printf("%lld %d is sleeping\n", time, x);
		else if (type == 'T')
			printf("%lld %d is thinking\n", time, x);
	}
	pthread_mutex_unlock(philo->printer);
	return (0);
}


void	ft_unlock_next_fork(t_philo *philo, int philo_number)
{
	int	i;

	i = 0;
	if (philo_number == philo->total_philo)
		i = 0;
	else
		i = philo_number + 1;
	pthread_mutex_unlock(&philo->forks[i]);
}


void	ft_lock_next_fork(t_philo *philo, int philo_number)
{
	int	i;

	i = 0;
	if (philo_number == philo->total_philo)
		i = 0;
	else
		i = philo_number + 1;
	pthread_mutex_lock(&philo->forks[i]);
	if (ft_print_messaje(philo, 'F', philo_number))
		ft_unlock_next_fork(philo, philo_number);
}

void	ft_put_last_meal(t_philo *philo, int philo_number)
{
	long long		time;

	time = ft_get_time_mili();
	philo->last_meals[philo_number] = time;
}


void	*routine(void *ptr)
{
	t_philo	*philo;
	int		philo_number;
	int		i;

	philo = (t_philo *)ptr;
	i = 0;
	pthread_mutex_lock(philo->counter_incrementer);
	philo_number = philo->counter++;
	pthread_mutex_unlock(philo->counter_incrementer);
	/////////////////////////////////////// he obtenido el numero de philosopho
	if ((philo_number % 2))
		usleep(200);
	ft_put_last_meal(philo, philo_number);
	while (philo->alive)
	{
		pthread_mutex_lock(&philo->forks[philo_number]);
		if (ft_print_messaje(philo, 'F', philo_number))
		{
			pthread_mutex_unlock(&philo->forks[philo_number]);
			return (NULL);
		}
		ft_lock_next_fork(philo, philo_number);
		if (ft_print_messaje(philo, 'E', philo_number))
			return (NULL);
		usleep(philo->time_to_eat * 1000);
		ft_put_last_meal(philo, philo_number);
		pthread_mutex_unlock(&philo->forks[philo_number]);
		ft_unlock_next_fork(philo, philo_number);
		if (ft_print_messaje(philo, 'S', philo_number))
			return (NULL);
		usleep(philo->time_to_sleep * 1000);
	}
	return (NULL);
}

int	start_sim(unsigned int x, t_philo *philo)
{
	pthread_t		philos[x];
	pthread_mutex_t forks[x];
	unsigned int	i;

	i = 0;
	while (i  != x)
	{
		pthread_mutex_init(forks + i++, NULL);
	}
	philo->forks = forks;
	i = 0;
	while (i  != x)
	{
		if(pthread_create(philos  + i, NULL, &routine, (void *)philo))
			return (1);
		++i;
	}
	i = 0;
	while (i  != x)
	{
		if(pthread_join(philos[i], NULL))
			return (1);
		++i;
	}
	return (0);
}

t_philo	*ft_init_philo(void)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->counter = 0;
	philo->total_philo = 200;
	philo->counter_incrementer = malloc(sizeof(pthread_mutex_t));
	if (!philo->counter_incrementer)
		return (NULL);
	pthread_mutex_init(philo->counter_incrementer, NULL);
	philo->printer = malloc(sizeof(pthread_mutex_t));
	if (!philo->printer)
		return (NULL);
	philo->death = malloc(sizeof(pthread_mutex_t));
	if (!philo->death)
		return (NULL);
	pthread_mutex_init(philo->printer, NULL);
	philo->last_meals = malloc(philo->total_philo * sizeof(long long));
	if (!philo->last_meals)
		return (NULL);
	philo->alive = 1;
	philo->time_to_die = 300;
	philo->time_to_sleep = 200;
	philo->time_to_eat = 200;
	return (philo);
}

int	main(void)
{
	t_philo	*philo;

	philo = ft_init_philo();
	if (!philo)
		return (-1);
	start_sim(philo->total_philo, philo);
	return (0);
}
#endif
#if 0

#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2

int shared_variable = 0;

void *increment_thread() {
    for (int i = 0; i < 100000; ++i) {
        shared_variable++; // Incrementa la variable compartida
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, increment_thread, NULL) != 0) {
            printf("Error creando el hilo %d\n", i);
            return 1;
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Valor final de la variable compartida: %d\n", shared_variable);

    return 0;
}


#endif
