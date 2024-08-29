/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:33:37 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/29 17:08:01 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

typedef struct s_data
{
	int num;
	pthread_mutex_t mutex;
}		t_data;

void	ft(void *arg)
{
	int i = -1;
	int *num;

	num =  (int *)arg;
	while (++i < 1000000)
	{
		pthread_mutex_lock(&num);
		(*num)++;
		pthread_mutex_unlock(&num);
	}
}

int	main(int argc, char *argv[])
{
	t_philo			p;
	pthread_t	t1;
	pthread_t	t2;
	t_data		*data;

	if (ft_parsing(argc, argv) == -1)
		return (1);
	ft_save_args(&p, argv);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	pthread_mutex_init(&data->mutex, NULL);
	data->num = 0;
	if (pthread_create(&t1, NULL, ft, data->num))
	{
		exit(1);
	}
	if (pthread_create(&t2, NULL, ft, data->num))
	{
		exit(1);
	}
	if (pthread_join(&t1, NULL))
	{
		exit (1);
	}
	printf("Num --> %d\n", data->num);
	return (0);
}
