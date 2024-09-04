/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:15 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/04 12:44:01 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_save_args(t_data *data, char *argv[])
{
	t_philo			*p;
	int				i;

	p = data->p;
	i = 0;
	data->id = ft_atoll(argv[1]);
	while (++i <= data->id)
	{
		p->time = ft_atoll(argv[2]);
		p->eat = ft_atoll(argv[3]);
		p->sleep = ft_atoll(argv[4]);
		if (argv[5])
			p->times_eat = ft_atoll(argv[5]);
		else
			p->times_eat = -1;
		if (p->time > 200 || p->eat > 200 || p->sleep > 200)
		{
			printf(RED"ERROR\nid: over the limit (200)%s\n", RESET);
			return (1);
		}
	}
	data->t_start = ft_get_current_time();
	return (0);
}

void	ft_create_threats(t_data *data)
{
	return ;
}

int	main(int argc, char *argv[])
{
	t_data			data;
	struct timeval		tmp;

	if (ft_parsing(argc, argv) == -1)
		return (1);
	ft_bzero(&data, sizeof(data));
	data.p = malloc(data.id * sizeof(t_philo));
	if (ft_save_args(&data, argv))
		return (1);
// args parsed and saved
	ft_create_threats(&data);
	free(data.p);
}
