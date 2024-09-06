/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:38:54 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/06 13:14:40 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

unsigned int	ft_get_current_time(void)
{
	struct timeval		tmp;
	unsigned int		current_time;

	gettimeofday(&tmp, NULL);
	current_time = (unsigned int)tmp.tv_sec * 1000 + tmp.tv_usec * 0.001;
	return (current_time);
}

unsigned int	ft_get_moment_time(t_data *data)
{
	return (ft_get_current_time() - data->t_start);
}

int	ft_dead_check(t_philo p)
{
	int		dead;

	dead = 1;
	pthread_mutex_lock(&p.check_dead);
	if (p.d_flag == 1)
		dead = 0;
	pthread_mutex_unlock(&p.check_dead);
	return (dead);
}

int	ft_printing(t_data *data, int i, int flag, char *action)
{
// flag => is dead?
// action => what action am I printing
	pthread_mutex_lock(&data->print);
	if (ft_dead_check(data->p[i]))
	{
		if (flag == DIE)
		{
			pthread_mutex_lock(&data->p->check_dead);
			data->p->d_flag = 1;
			pthread_mutex_unlock(&data->p->check_dead);
		}
		printf(action, ft_get_moment_time(data), data->p[i].id, RESET);
	}
	pthread_mutex_unlock(&data->print);
	return (0);
}
