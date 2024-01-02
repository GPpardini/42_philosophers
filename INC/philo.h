/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:41:09 by gpardini          #+#    #+#             */
/*   Updated: 2023/11/15 14:43:50 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	size_t			start_time;
	size_t			last_meal;
	size_t			eating_time;
	size_t			sleep_time;
	size_t			philo_spaw;
	int				philo_count;
	int				*monitor_dead_flag;
	int				*monitor_eat_flag;
	int				is_eating;
	int				eat_count;
	pthread_mutex_t	*right_lock;
	pthread_mutex_t	*left_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*finish_lock;
	pthread_mutex_t	meal_lock;
	pthread_t		thread;
}					t_philo;

typedef struct t_data
{
	int				philo_count;
	size_t			philo_spaw;
	size_t			eating_time;
	size_t			sleep_time;
	int				meal_count;
	int				monitor_dead_flag;
	int				monitor_eat_flag;
	pthread_t		monitor;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	finish_lock;
}					t_data;

int		ft_atoi(char *str);
int		check_is_num(char **str);
void	eat(t_philo *philo);
void	dream(t_philo *philo);
void	think(t_philo *philo);
void	routine(t_philo *philos);
void	*monitor(void *info);
void	start_threads(t_philo *philos, t_data *data, int philo_count);	
t_philo	*start_philos(t_data *data);
void	start_forks(t_data *data);
void	start_data(char **argv, t_data *data);
void	msg(t_philo *philo, char *msg);
int		ft_usleep(size_t ms);
size_t	get_time(void);
int		philo_dead_flag(t_philo *philo);
int		monitor_end_program(t_philo *philos, int i);
void	start_philos_data(t_data *data, t_philo *philos, int i);
void	check_monitor_eat_flag(t_philo *philo);
void	take_forks(t_philo *philo);

#endif
