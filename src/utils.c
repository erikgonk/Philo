/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:36:34 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/26 17:40:45 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

int	ft_parsing(int argc, char *argv[])
{
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("error\nargs: we need 4-5 args to work\n");
		return (-1);
	}
	while (argv[++i])
	{
		if (ft_atoll(argv[i]) < 0)
		{
			printf("error\nargs: %s not valid\n", argv[i]);
			return (-1);
		}
	}
	return (0);
}

void	ft_save_args(t_philo *p, char *argv[])
{
	p->num = ft_atoll(argv[1]);
	p->time = ft_atoll(argv[2]);
	p->eat = ft_atoll(argv[3]);
	p->sleep = ft_atoll(argv[4]);
	if (argv[5])
		p->times_eat = ft_atoll(argv[5]);
	else
		p->times_eat = -1;
}
