/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:19:23 by gpardini          #+#    #+#             */
/*   Updated: 2023/11/22 12:33:51 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->left_lock);
		msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_lock);
		msg(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_lock);
		msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_lock);
		msg(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->is_eating = 1;
	philo->eat_count = philo->eat_count - 1;
	check_monitor_eat_flag(philo);
	msg(philo, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->eating_time);
	pthread_mutex_lock(&philo->meal_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->meal_lock);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->right_lock);
		pthread_mutex_unlock(philo->left_lock);
	}
	else
	{
		pthread_mutex_unlock(philo->left_lock);
		pthread_mutex_unlock(philo->right_lock);
	}
}

void	dream(t_philo *philo)
{
	if (philo->philo_count % 2 != 0)
		usleep(1);
	msg(philo, "is sleeping");
	ft_usleep(philo->sleep_time);
}

void	think(t_philo *philo)
{
	msg(philo, "is thinking");
}

void	routine(t_philo *philo)
{
	if (philo->philo_count == 1)
	{
		msg(philo, "has taken a fork");
		ft_usleep(philo->philo_spaw);
	}
	while (!philo_dead_flag(philo) && philo->eat_count != 0)
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
}
