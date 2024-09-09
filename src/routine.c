/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:54:03 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/09 15:09:19 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_action(t_philo *p, char *action)
{
	pthread_mutex_lock(&p->print);
	printf(action, ft_get_moment_time(p), p->id, RESET);
	pthread_mutex_unlock(&p->print);
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(&p->fork1);
	ft_print_action(p, ACT_FORK);
	if (&p->fork1 != &p->fork2)
	{
		pthread_mutex_lock(&p->fork2);
		ft_print_action(p, ACT_FORK);
		pthread_mutex_lock(&p->last_meal);
		p->times_eat--;
		pthread_mutex_unlock(&p->last_meal);
		ft_print_action(p, ACT_EAT);
		pthread_mutex_unlock(&p->fork2);
		usleep(p->eat * 1000);
	}
	pthread_mutex_lock(&p->fork1);
}

void	*ft_routine(void *data)
{
	t_philo		*p;

	p = data;
	pthread_mutex_lock(&p->check_dead);
	pthread_mutex_unlock(&p->check_dead);
	pthread_mutex_lock(&p->check_dead);
	printf("id -> %lld\n", p->id);
	while (p->d_flag == 0)
	{
		if (p->id % 2 != 0)
			usleep((p->eat - 1) * 1000);
		ft_eat(p);
		if (p->times_eat < 0)
		{
			ft_print_action(p, ACT_DIE);
			break ;
		}
		if (p->times_eat != 0)
		{
			ft_print_action(p, ACT_SLEEP);
			usleep(p->sleep * 1000);
			ft_print_action(p, ACT_THINK);
		}
	}
	pthread_mutex_unlock(&p->check_dead);
}
