/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:26:37 by gpardini          #+#    #+#             */
/*   Updated: 2023/11/22 12:30:12 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

void	start_data(char **argv, t_data *data)
{
	data->philo_count = ft_atoi(argv[1]);
	data->philo_spaw = ft_atoi(argv[2]);
	data->eating_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->meal_count = -1;
	data->monitor_dead_flag = 0;
	data->monitor_eat_flag = ft_atoi(argv[1]);
	if (argv[5])
		data->meal_count = ft_atoi(argv[5]);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->finish_lock, NULL);
}

void	start_forks(t_data *data)
{
	int	i;

	i = 0;
	data->fork_lock = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->fork_lock[i], NULL);
		i++;
	}
}

void	start_philos_data(t_data *data, t_philo *philos, int i)
{
	philos[i].id = i + 1;
	philos[i].start_time = get_time();
	philos[i].last_meal = get_time();
	philos[i].eating_time = data->eating_time;
	philos[i].sleep_time = data->sleep_time;
	philos[i].philo_spaw = data->philo_spaw;
	philos[i].philo_count = data->philo_count;
	philos[i].monitor_dead_flag = &data->monitor_dead_flag;
	philos[i].monitor_eat_flag = &data->monitor_eat_flag;
	philos[i].is_eating = 0;
	philos[i].eat_count = data->meal_count;
	philos[i].write_lock = &data->write_lock;
	philos[i].dead_lock = &data->dead_lock;
	philos[i].finish_lock = &data->finish_lock;
}

t_philo	*start_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->philo_count);
	i = 0;
	while (i < data->philo_count)
	{
		start_philos_data(data, philos, i);
		if (i == 0)
		{
			philos[0].right_lock = &data->fork_lock[0];
			philos[0].left_lock = &data->fork_lock[data->philo_count - 1];
		}
		else
		{
			philos[i].right_lock = &data->fork_lock[i];
			philos[i].left_lock = &data->fork_lock[i - 1];
		}
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		i++;
	}
	return (philos);
}

void	start_threads(t_philo *philos, t_data *data, int philo_count)
{
	int	i;

	i = 0;
	pthread_create(&data->monitor, NULL, monitor, philos);
	while (i < philo_count)
	{
		pthread_create(&philos[i].thread, NULL, (void *)routine, &philos[i]);
		i++;
	}
	i = 0;
	pthread_join(data->monitor, NULL);
	while (i < philo_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
