/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:54:03 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/15 15:58:11 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_check_death(t_data *data)
{
	pthread_mutex_lock(&data->check_dead);
	if (data->d_flag == 1)
	{
		pthread_mutex_unlock(&data->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->check_dead);
	return (0);
}

int	ft_usleep(t_philo *p, long long int to_sleep)
{
	unsigned int	time;

	time = ft_get_moment_time(p);
	if (ft_check_death(p->data))
		return (1);
	while (!ft_check_death(p->data) && ft_get_moment_time(p) - time < to_sleep)
		usleep(1000);
	return (0);
}

void	ft_print_action(t_philo *p, char *action)
{
	pthread_mutex_lock(&p->data->print);
	if (!ft_check_death(p->data))
		printf(action, ft_get_moment_time(p), p->id, RESET);
	pthread_mutex_unlock(&p->data->print);
}

void	ft_eat(t_philo *p)
{
	if (ft_check_death(p->data))
		return ;
	pthread_mutex_lock(&p->fork1);
	ft_print_action(p, ACT_FORK);
	if (&p->fork1 != p->fork2)
	{
		pthread_mutex_lock(p->fork2);
		ft_print_action(p, ACT_FORK);
		pthread_mutex_lock(&p->god);
		p->l_meal = ft_get_moment_time(p);
		p->times_eat--;
		pthread_mutex_unlock(&p->god);
		ft_print_action(p, ACT_EAT);
		ft_usleep(p, p->data->eat);
		pthread_mutex_unlock(p->fork2);
	}
	else
		ft_usleep(p, p->data->time);
	pthread_mutex_unlock(&p->fork1);
}

void	*ft_routine(void *data)
{
	t_philo		*p;

	p = data;
	pthread_mutex_lock(&p->data->routine);
	pthread_mutex_unlock(&p->data->routine);
	if (p->id % 2 != 0 && p->data->num > 1)
		ft_usleep(p, (p->data->eat - 1));
	while (!ft_check_death(p->data))
	{
		ft_eat(p);
		if (p->times_eat == 0)
			break ;
		ft_print_action(p, ACT_SLEEP);
		ft_usleep(p, p->data->sleep);
		ft_print_action(p, ACT_THINK);
	}
}
