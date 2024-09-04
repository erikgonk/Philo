/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:15 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/04 14:04:33 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_save_args(t_data *data, char *argv[], int i)
{
	t_philo			*p;

	p = data->p;
	data->num = ft_atoll(argv[1]);
	while (++i < data->num)
	{
		data->p[i].id = i;
		data->p[i].time = ft_atoll(argv[2]);
		data->p[i].eat = ft_atoll(argv[3]);
		data->p[i].sleep = ft_atoll(argv[4]);
		if (argv[5])
			data->p[i].times_eat = ft_atoll(argv[5]);
		else
			data->p[i].times_eat = -1;
		if (data->p[i].time > 200 || data->p[i].eat > 200 ||
				data->p[i].sleep > 200)
		{
			printf(RED"ERROR\nid: over the limit (200)%s\n", RESET);
			free(data->p);
			return (1);
		}
	}
	return (0);
}

int	ft_create_threats(t_data *data, char **args)
{
	int			i;

	i = -1;
	if (data->num < 1)
		return (ft_exit("ERROR:\nargs: not enough philosophers\n"));
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
		return (ft_exit("ERROR:\nmalloc\n"));
	if (ft_save_args(&data, argv, -1))
		return (1);
	data.t_start = ft_get_current_time();
// args parsed and saved
	ft_create_threats(&data, argv);
	free(data.p);
	return (0);
}
