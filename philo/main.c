/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:21:54 by samusanc          #+#    #+#             */
/*   Updated: 2023/07/26 18:33:40 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>


#if 1

#endif

#if 0
//comer significa bloquear 2 tenedores y hacer un sleep de x tiempo
//dormir significa hacer un sleep de x tiempo
//pensar es cualquier tiempo en el que las dos acciones anteriores no se esten realizando
//morir es cuando el tiempo del filosofo desde la ultima comida ha sido superado con su tiempo de muerte

long long	ft_get_time_mili(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (time);
}

void	*ft_free(void **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

int	ft_print_messaje(t_philo *philo, int x, char *menssage)
{
	long long		time;

	pthread_mutex_lock(philo->printer);
	if (philo->alive)
	{
		time = ft_get_time_mili();
		printf("%lld %d %s\n", time, x, menssage);
	}
	pthread_mutex_unlock(philo->printer);
	return (0);
	x = 0;
	menssage = NULL;
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
	ft_print_messaje(env->philo, philo_number, FORK);
}

void	ft_lock_fork(t_env *env, int philo_number)
{
	pthread_mutex_lock(&env->forks[philo_number]);
	ft_print_messaje(env->philo, philo_number, FORK);
}

void	ft_put_last_meal(t_philo *philo, int philo_number)
{
	long long		time;

	time = ft_get_time_mili();
	philo->last_meals[philo_number] = time;
}


void	ft_check_death(t_env *env, unsigned int i)
{
	long long	time;

	time = ft_get_time_mili();
	pthread_mutex_lock(env->philo->printer);
	if (env->philo->last_meals[i] != -1 && env->philo->last_meals[i] + \
	env->time_to_die < time && env->philo->alive)
	{
		env->philo->alive = 0;
		printf("%lld %d %s\n", time, i, DEAD);
		printf("%lld:actual time\n%lld:last meal\n%lld:next save meal\n", time, env->philo->last_meals[i], env->philo->last_meals[i] + env->time_to_die - 1);
	}
	pthread_mutex_unlock(env->philo->printer);
}

void	*inspection(void *ptr)
{
	t_philo	*philo;
	t_env	*env;
	unsigned int		i;

	env = (t_env *)ptr;
	philo = env->philo;
	i = 0;
	while (philo->alive)
	{
		i = 0;
		while (i != env->total_philo)
		{
			pthread_mutex_lock(&philo->id[i]);
			ft_check_death(env, i);
			pthread_mutex_unlock(&philo->id[i]);
			usleep(300);
			++i;
		}
		if (!philo->alive)
			break ;
		usleep((env->time_to_die / 2) * 1000);
	}
	return (NULL);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	t_env	*env;
	int		philo_number;
	int		i;

	env = (t_env *)ptr;
	philo = env->philo;
	i = 0;
	pthread_mutex_lock(philo->counter_incrementer);
	philo_number = philo->counter++;
	pthread_mutex_unlock(philo->counter_incrementer);
	pthread_mutex_lock(philo->counter_incrementer);
	pthread_mutex_unlock(philo->counter_incrementer);
	if ((philo_number % 2))
		usleep(200);
	ft_put_last_meal(philo, philo_number);
	while (philo->alive)
	{
		ft_lock_fork(env, philo_number);
		ft_lock_next_fork(env, philo_number);
		ft_print_messaje(philo, philo_number, EAT);
		usleep(env->time_to_eat * 1000);
		ft_unlock_fork(env, philo_number);
		ft_unlock_next_fork(env, philo_number);
		pthread_mutex_lock(&philo->id[philo_number]);
		ft_put_last_meal(philo, philo_number);
		pthread_mutex_unlock(&philo->id[philo_number]);
		ft_print_messaje(philo, philo_number, SLEEP);
		usleep(env->time_to_sleep * 1000);
		ft_print_messaje(philo, philo_number, THINK);
	}
	return (NULL);
}

int	start_sim(t_env *env)
{
	pthread_t		philos[env->total_philo];
	pthread_t		caronte;
	unsigned int	i;

	i = 0;
	if(pthread_create(&caronte, NULL, &inspection, (void *)env))
			return (1);
	while (i != env->total_philo)
	{
		if(pthread_create(philos  + i, NULL, &routine, (void *)env))
			return (1);
		++i;
	}
	i = 0;
	while (i != env->total_philo)
	{
		if(pthread_join(philos[i], NULL))
			return (1);
		++i;
	}
	return (0);
}

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
	return (NULL);
}

void	ft_fill_meals(long long *meals, unsigned int total)
{
	unsigned int	i;

	i = 0;
	while (i != total)
	{
		meals[i] = -1;
		++i;
	}
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
	philo->last_meals = malloc(total_philo * sizeof(long long));
	if (!philo->last_meals)
		return ((t_philo *)ft_free_philo(philo));
	ft_fill_meals(philo->last_meals, total_philo);
	return (philo);
}

void	*ft_free_env(t_env *env)
{
	if (!env)
		return (NULL);
	ft_free((void **)&env->forks);
	return ((t_philo *)ft_free_philo(env->philo));
}

t_env	*ft_init_env(void)
{
	t_env			*env;
	t_philo			*philo;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->total_philo = 200;
	env->time_to_die = 410;
	env->time_to_sleep = 200;
	env->time_to_eat = 200;
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

int	main(void)
{
	t_env *env;


	env = ft_init_env();
	if (!env)
		return (-1);
	start_sim(env);
	return (0);
}


#endif
#if 0

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
