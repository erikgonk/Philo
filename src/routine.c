/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:54:03 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/08 10:09:29 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_routine(void *data)
{
	t_philo		*p;

	p = data;

	pthread_mutex_lock(&p->check_dead);
	pthread_mutex_unlock(&p->check_dead);
// cue with threads
	if (ft_dead_check(p) && p->id % 2 != 0)
		usleep((p->eat - 1) * 1000);
// sleep if it's odd philo
	
	return (0);
}
