/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:30:51 by gpardini          #+#    #+#             */
/*   Updated: 2023/11/22 12:37:16 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

void	check_monitor_eat_flag(t_philo *philo)
{
	if (philo->eat_count == 0)
	{
		pthread_mutex_lock(philo->finish_lock);
		*philo->monitor_eat_flag = *philo->monitor_eat_flag - 1;
		pthread_mutex_unlock(philo->finish_lock);
	}
}

int	philo_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->monitor_dead_flag) == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
}

int	monitor_end_program(t_philo *philos, int i)
{
	if (*philos[i].monitor_eat_flag == 0)
	{
		pthread_mutex_lock(philos[i].dead_lock);
		pthread_mutex_unlock(&philos[i].meal_lock);
		*philos[0].monitor_dead_flag = 1;
		pthread_mutex_unlock(philos[i].dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&philos[i].meal_lock);
	msg(&philos[i], "died");
	pthread_mutex_lock(philos[i].dead_lock);
	*philos[0].monitor_dead_flag = 1;
	pthread_mutex_unlock(philos[i].dead_lock);
	return (0);
}

int	monitor_loop(t_philo *philos)
{
	int		i;
	size_t	time;

	i = 0;
	while (i < philos[0].philo_count)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		time = get_time() - philos[i].last_meal;
		pthread_mutex_unlock(&philos[i].meal_lock);
		pthread_mutex_lock(&philos[i].meal_lock);
		pthread_mutex_lock(philos[i].finish_lock);
		if (time >= philos[0].philo_spaw || *philos[i].monitor_eat_flag == 0)
		{
			pthread_mutex_unlock(philos[i].finish_lock);
			monitor_end_program(philos, i);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(philos[i].finish_lock);
			pthread_mutex_unlock(&philos[i].meal_lock);
		}
		i++;
	}
	return (1);
}

void	*monitor(void *info)
{
	t_philo	*philos;

	philos = (t_philo *)info;
	while (1)
	{
		if (!monitor_loop(philos))
			break ;
	}
	return (info);
}
