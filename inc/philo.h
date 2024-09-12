/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:41:46 by erigonza          #+#    #+#             */
/*   Updated: 2024/09/12 13:37:24 by erigonza         ###   ########.fr       */
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

# define ACT_FORK "[%u] %lld has taken a fork%s\n"
# define ACT_EAT "\x1B[32m[%u] %lld is eating%s\n"
# define ACT_SLEEP "\x1B[36m[%u] %lld is sleeping%s\n"
# define ACT_THINK "\x1B[33m[%u] %lld is thinking%s\n"
# define ACT_DIE "\x1B[31m[%u] %lld died%s\n"

# define E_ID "ERROR\nid: over the limit (200)\n"
# define E_INIT_T "ERROR: init thread\n"
# define E_MALLOC "ERROR:\nmalloc\n"
# define E_ARGS "ERROR\nargs: we need 4-5 args to work\n"
# define E_ARG1 "ERROR\narg_1: philosophers required\n"
# define E_PHILOS "ERROR:\nargs: not enough philosophers\n"
# define E_CREATE "ERROR:\ncreating thread\n"
# define E_ARGS_NUM "ERROR\nargs: 0 not valid\n"

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

enum
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
};

typedef struct s_philo
{
	pthread_mutex_t		print;
	pthread_mutex_t		fork1;
	pthread_mutex_t		*fork2;
	pthread_mutex_t		last_meal;
	pthread_mutex_t		check_dead;
	int					d_flag;// 0 alive 1 dead
	unsigned int		t_start;
	unsigned int		t_end;
	pthread_t			philo;
	long long int		num;
	long long int		id;
	long long int		time;
	long long int		eat;
	long long int		sleep;
	long long int		times_eat;
	struct s_data		*data;
	
}		t_philo;

typedef struct s_data
{
	pthread_mutex_t		print;
	pthread_mutex_t		routine;
	int					stop_routine;// 0 some alive 1 all dead
	long long int		num;
	t_philo				*p;
}		t_data;

// routine
void					*ft_routine(void *data);
void					ft_print_action(t_philo *p, char *action);
// utils exec
unsigned int			ft_get_current_time(void);
unsigned int			ft_get_moment_time(t_philo *p);
int						ft_printing(t_data *data, int i, int flag, char *action);
int						ft_printing(t_data *data, int i, int flag, char *action);
int						ft_save_normi(t_data *data, char  *argv[], int i);
// utils
int						ft_exit(char *error);
int						ft_parsing(int argc, char *argv[]);
void					ft_bzero(void *s, size_t n);
int						ft_strcmp(char *s1, char *s2);
long long int			ft_atoll(char *str);

#endif
