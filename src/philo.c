/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:08:15 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/02 12:50:13 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_save_args(t_data *data, char *argv[])
{
	t_philo			*p;
	int				i;

	p = data->p;
	i = 0;
	data->num = ft_atoll(argv[1]);
	while (++i <= data->num)
	{
		p->time = ft_atoll(argv[2]);
		p->eat = ft_atoll(argv[3]);
		p->sleep = ft_atoll(argv[4]);
		if (argv[5])
			p->times_eat = ft_atoll(argv[5]);
		else
			p->times_eat = -1;
	}
}

void	ft_create_threats(&data)
{
}

int	main(int argc, char *argv[])
{
	t_data			data;

	if (ft_parsing(argc, argv) == -1)
		return (1);
	ft_bzero(&data, sizeof(data));
	data.p = malloc(data.num * sizeof(t_philo));
	ft_save_args(&data, argv);
// args parsed and saved
	ft_create_threats(&data);
}
