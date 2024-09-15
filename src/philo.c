/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:15 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/15 15:58:03 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_exit_free(t_data *data, char *error)
{
	if (data->p)
		free(data->p);
	if (error)
	{
		printf(RED);
		printf("%s%s", error, RESET);
	}
	return (1);
}

int	ft_save_args(t_data *data, char *argv[], int i)
{
	t_philo			*p;

	p = data->p;
	data->num = ft_atoll(argv[1]);
	if (pthread_mutex_init(&data->routine, NULL))
		return (ft_exit_free(data, E_INIT_T));
	if (pthread_mutex_init(&data->check_dead, NULL))
		return (ft_exit(E_INIT_T));
	if (data->num > 200)
		return (ft_exit_free(data, E_ID));
	data->time = ft_atoll(argv[2]);
	data->eat = ft_atoll(argv[3]);
	data->sleep = ft_atoll(argv[4]);
	while (++i < data->num)
	{
		data->p[i].data = data;
		if (ft_save_normi(data, argv, i) == 1)
			return (1);
	}
	data->p[0].fork2 = &data->p[data->num - 1].fork1;
	if (data->num <= 0)
		return (ft_exit_free(data, E_ARGS_NUM));
	return (0);
}

int	ft_start_routine(t_data *data)
{
	int		i;

	i = -1;
	pthread_mutex_lock(&data->routine);
	while (++i < data->num)
	{
		if (pthread_create(&data->p[i].philo, NULL, &ft_routine,
				&data->p[i]))
			ft_exit_free(data, E_CREATE);
	}
	data->t_start = ft_get_current_time();
	pthread_mutex_unlock(&data->routine);
	return (0);
}

void	ft_destroy(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->num)
		pthread_join(data->p[i].philo, NULL);
	i = -1;
	while (++i < data->num)
	{
		pthread_mutex_destroy(&data->p[i].god);
		pthread_mutex_destroy(&data->p[i].fork1);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->routine);
	pthread_mutex_destroy(&data->check_dead);
	ft_exit_free(data, NULL);
}

void	ft_godfather(t_data *data)
{
	int	i;
	int	flag_meals;

	flag_meals = 0;
	while (!ft_check_death(data) && flag_meals == 0)
	{
		i = -1;
		flag_meals = 1;
		while (++i < data->num)
		{
			pthread_mutex_lock(&data->p->god);
			if (data->p[i].times_eat != 0)
				flag_meals = 0;
			if (ft_get_moment_time(&data->p[i]) - data->p[i].l_meal >= data->time && data->p[i].times_eat != 0)
				ft_printing(data, i, DIE, ACT_DIE);
			pthread_mutex_unlock(&data->p->god);
		}
	}
	ft_destroy(data);
}


int	main(int argc, char *argv[])
{
	t_data				data;

	if (ft_parsing(argc, argv) == 1)
		return (1);
	ft_bzero(&data, sizeof(data));
	data.p = malloc(ft_atoll(argv[1]) * sizeof(t_philo));
	if (!data.p)
		return (ft_exit(E_MALLOC));
	if (ft_save_args(&data, argv, -1))
		return (ft_exit_free(&data, NULL));
// args parsed and saved & init mutexes
	if (ft_start_routine(&data))
		return (1);
	ft_godfather(&data);
	return (0);
}
