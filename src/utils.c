/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:36:34 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/05 13:00:51 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_parsing(int argc, char *argv[])
{
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (ft_exit("ERROR\nargs: we need 4-5 args to work\n"));
	if (argv[1] <= 0)
		return (ft_exit("ERROR\narg_1: philosophers required\n"));
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

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_bzero(void *s, size_t n)
{
	while (n-- > 0)
		*((unsigned char *)s++) = 0;
}
