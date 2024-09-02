/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:41:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/02 12:51:29 by erigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define BLUE "\x1B[34m"
# define GREEN "\x1B[32m"
# define RESET "\x1B[0m"
# define CYAN "\x1B[36m"
# define MAGENTA "\x1B[35m"
# define YELLOW "\x1B[33m"
# define RED "\x1B[31m"
# define WHITE "\x1b[37m"

# define ACT_FORK "[%u] %d has taken a fork%s\n"
# define ACT_EAT "\x1B[32m[%u] %d is eating%s\n"
# define ACT_SLEEP "\x1B[36m[%u] %d is sleeping%s\n"
# define ACT_THINK "\x1B[33m[%u] %d is thinking%s\n"
# define ACT_DIE "\x1B[31m[%u] %d died%s\n"

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
	int					flag;// if 0 works, if 1 everbody died
	unsigned int		t_end;
	long long int		id;
	long long int		time;
	long long int		eat;
	long long int		sleep;
	long long int		times_eat;
	
}		t_philo;

typedef struct s_data
{
	unsigned int		t_start;
	long long int		num;
	t_philo				*p;
}		t_data;

long long int		ft_atoll(char *str);
int					ft_parsing(int argc, char *argv[]);
void				ft_save_args(t_data *data, char *argv[]);
// libft
void				ft_bzero(void *s, size_t n);
#endif
