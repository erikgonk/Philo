/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:36:34 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/16 11:00:07 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_parsing(int argc, char *argv[])
{
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (ft_exit(E_ARGS));
	if (argv[1] <= 0)
		return (ft_exit(E_ARG1));
	while (argv[++i])
	{
		if (ft_atoll(argv[i]) < 0)
		{
			printf(RED"ERROR\nargs: %s not valid\n%s", argv[i], RESET);
			return (1);
		}
	}
	return (0);
}

void	ft_destroy(t_data *data, int num)
{
	int		i;

	i = -1;
	while (++i < num)
		pthread_join(data->p[i].philo, NULL);
	i = -1;
	while (++i < num)
	{
		pthread_mutex_destroy(&data->p[i].god);
		pthread_mutex_destroy(&data->p[i].fork1);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->routine);
	pthread_mutex_destroy(&data->check_dead);
	ft_exit_free(data, NULL);
}

int	ft_exit(char *error)
{
	printf(RED);
	if (error)
		printf("%s", error);
	printf(RESET);
	return (1);
}

long long int	ft_atoll(char *str)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
	{
		i++;
	}
	if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	if (res < 0)
		return (-1);
	return (res);
}

void	ft_bzero(void *s, size_t n)
{
	while (n-- > 0)
		*((unsigned char *)s++) = 0;
}
