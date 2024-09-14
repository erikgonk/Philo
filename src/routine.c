/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:54:03 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/14 16:11:42 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_check_philo_death(t_philo *p, unsigned int time)
{
	if ((time - p->l_meal) > p->data->time)
	{
		printf(ACT_DIE, time, p->id, RESET);
		p->data->d_flag = 1;
		p->d_flag = 1;
		return (1);
	}
}
int	ft_usleep(t_philo *p, long long int to_sleep)
{
	unsigned int	tmp;
	unsigned int time;

	time = ft_get_moment_time(p);
	tmp = 0;
	if (p->data->d_flag == 1)
		return (1);
	while (!ft_check_philo_death(p, time) && tmp < to_sleep)
	{
		//printf("------------------> [%u] %u < %lld && %u < %lld\n", ft_get_moment_time(p), p->data->t_start + tmp, p->data->time, tmp, to_sleep);
		usleep(1000);
		tmp += 1;
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
	printf(action, ft_get_moment_time(p), p->id, RESET);
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(&p->fork1);
	if (p->data->d_flag == 1)
	{
		pthread_mutex_unlock(&p->fork1);
		return ;
	}
	ft_print_action(p, ACT_FORK);
	if (&p->fork1 != p->fork2 && p->data->d_flag == 0)
	{
		pthread_mutex_lock(p->fork2);
		if (p->data->d_flag == 1)
		{
			pthread_mutex_unlock(&p->fork1);
			pthread_mutex_unlock(p->fork2);
			return ;
		}
		ft_print_action(p, ACT_FORK);
		p->l_meal = ft_get_moment_time(p);
		p->times_eat--;
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
	pthread_mutex_lock(&p->data->routine);
	pthread_mutex_unlock(&p->data->routine);
	printf("time -> %u, last meal -> %u\n", p->data->t_start, p->l_meal);
	while (p->data->d_flag == 0)
	{
		if (p->id % 2 != 0 && p->data->num > 1)
			ft_usleep(p, (p->data->eat - 1));
		ft_eat(p);
		if (p->times_eat >= 0 && p->times_eat < 0)
		{
			p->t_end = 1;
			break ;
		}
		if (p->data->d_flag == 0)
		{
			pthread_mutex_lock(p->fork2);
			ft_print_action(p, ACT_SLEEP);
			pthread_mutex_unlock(p->fork2);
			ft_usleep(p, p->data->sleep);
			pthread_mutex_lock(p->fork2);
			ft_print_action(p, ACT_THINK);
			pthread_mutex_unlock(p->fork2);
		}
	}
}
