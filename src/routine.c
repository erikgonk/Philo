/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:54:03 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/14 12:09:52 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_usleep(t_philo *p, long long int to_sleep)
{
	unsigned int	time;
	unsigned int	tmp;
 
	tmp = 0;
	time = ft_get_moment_time(p);
	if (p->data->d_flag == 1)
		return (1);
	if (!((time + tmp) < p->data->time && tmp < to_sleep))
	{
		pthread_mutex_lock(&p->check_dead);
		p->data->d_flag = 1;
		p->d_flag = 1;
		pthread_mutex_unlock(&p->check_dead);
		return (1);
	}
	while ((time + tmp) < p->data->time && tmp < to_sleep && p->data->d_flag == 0)
	{
		pthread_mutex_lock(&p->check_dead);
		usleep(1000);
		tmp += 1;
		pthread_mutex_unlock(&p->check_dead);
	}
	return (0);
// check if it dies while doing the usleep
// if no: do the usleep and rutrn 0
// if yes: time_to_die - actual_time < to_sleep: do time_to_die - actual_time
}

void	ft_print_action(t_philo *p, char *action)
{
	if (p->data->d_flag == 1)
		return ;
	pthread_mutex_lock(&p->print);
	printf(action, ft_get_moment_time(p), p->id, RESET);
	pthread_mutex_unlock(&p->print);
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(&p->fork1);
	if (p->data->d_flag == 1)
		return ;
	ft_print_action(p, ACT_FORK);
	if (&p->fork1 != p->fork2 && p->data->d_flag == 0)
	{
		if (p->data->d_flag == 1)
		{
			pthread_mutex_lock(&p->fork1);
			pthread_mutex_unlock(p->fork2);
			return ;
		}
		pthread_mutex_lock(p->fork2);
		ft_print_action(p, ACT_FORK);
		pthread_mutex_lock(&p->last_meal);
		p->times_eat--;
		pthread_mutex_unlock(&p->last_meal);
		ft_print_action(p, ACT_EAT);
		ft_usleep(p, p->data->eat);
		pthread_mutex_unlock(p->fork2);
	}
	else if (p->data->d_flag == 0)
		ft_usleep(p, p->data->eat);
	pthread_mutex_unlock(&p->fork1);
}

void	*ft_routine(void *data)
{
	t_philo		*p;

	p = data;
	pthread_mutex_lock(&p->check_dead);
	pthread_mutex_unlock(&p->check_dead);
	while (p->data->d_flag == 0)
	{
		if (p->id % 2 != 0 && p->data->d_flag == 0)
			ft_usleep(p, (p->data->eat - 1));
		ft_eat(p);
		if (p->times_eat >= 0 && p->times_eat < 0)
		{
			p->t_end = 1;
			break ;
		}
		ft_print_action(p, ACT_SLEEP);
		if (p->data->d_flag == 0)
			ft_usleep(p, p->data->sleep);
		ft_print_action(p, ACT_THINK);
	}
}
