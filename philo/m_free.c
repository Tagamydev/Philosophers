/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:41:28 by samusanc          #+#    #+#             */
/*   Updated: 2023/10/15 15:41:40 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
