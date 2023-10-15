/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:43:45 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:43:57 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
