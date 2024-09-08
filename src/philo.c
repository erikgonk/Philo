/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:15 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/08 15:19:52 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_save_args(t_data *data, char *argv[], int i)
{
	t_philo			*p;

	p = data->p;
	data->num = ft_atoll(argv[1]);
	if (pthread_mutex_init(&data->routine, NULL))
		return (ft_exit(E_INIT_T));
	if (pthread_mutex_init(&data->print, NULL))
		return (ft_exit(E_INIT_T));
	while (++i < data->num)
	{
		if (ft_save_normi(data, argv, i) == 1)
			return (1);
		if (data->p[i].time > 200 || data->p[i].eat > 200 ||
				data->p[i].sleep > 200)
		{
			free(data->p);
			return (ft_exit(E_ID));
		}
		p[i].t_start = ft_get_current_time();
	}
	if (data->num <= 0)
		return (ft_exit(E_ARGS_NUM));
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
		{
			data->stop_routine = 1;
			ft_exit(E_CREATE);
		}
	}
	pthread_mutex_unlock(&data->routine);
	i = -1;
	while (++i < data->num)
		pthread_join(data->p[i].philo, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data				data;

	if (ft_parsing(argc, argv) == 1)
		return (1);
	ft_bzero(&data, sizeof(data));
	data.p = malloc(data.num * sizeof(t_philo));
	if (!data.p)
		return (ft_exit(E_MALLOC));
	if (ft_save_args(&data, argv, -1))
		return (1);
// args parsed and saved & init mutexes
	if (ft_start_routine(&data))
		return (1);
	free(data.p);
	return (0);
}
