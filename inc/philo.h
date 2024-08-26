/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:41:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/08/26 17:39:11 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// threads
# include <pthread.h>
// malloc, free
# include <stdlib.h>
// printf & write
# include <stdio.h>
# include <unistd.h>
// memset
# include <string.h>
// gettimeofday
# include <sys/time.h>

typedef struct s_philo
{
	long long int		num;
	long long int		time;
	long long int		eat;
	long long int		sleep;
	long long int		times_eat;
}		t_philo;

long long int		ft_atoll(char *str);
int					ft_parsing(int argc, char *argv[]);
void				ft_save_args(t_philo *p, char *argv[]);

#endif
