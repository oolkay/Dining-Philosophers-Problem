/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:09:52 by omer/baha         #+#    #+#             */
/*   Updated: 2023/10/07 14:20:39 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../includes/philo.h"

static int	ft_philo_sleep(t_philo *philo)
{
	if (ft_print(philo, SLEEP) == -1)
		return (-1);
	my_sleep(philo->table->time_to_sleep);
	if (ft_print(philo, THINK) == -1)
		return (-1);
	return (1);
}

static int	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->nb_eat_mutex);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->table->nb_eat_mutex);
	pthread_mutex_lock(&philo->table->last_eat_mutex);
	philo->last_eat = philo_get_time() - philo->table->start_time;
	pthread_mutex_unlock(&philo->table->last_eat_mutex);
	if (ft_print(philo, EAT) == -1)
		return (-1);
	my_sleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->id]);
	pthread_mutex_unlock(&philo->table->fork_mutex[(philo->id + 1)
		% philo->table->nb_philo]);
	ft_philo_sleep(philo);
	return (1);
}

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mutex[philo->id]);
	if (ft_print(philo, TAKE_FORK) == -1)
		return (-1);
	if (philo->table->nb_philo == 1)
	{
		my_sleep(philo->table->time_to_die);
		pthread_mutex_unlock(&philo->table->fork_mutex[philo->id]);
		ft_print(philo, DIE);
		return (-1);
	}
	pthread_mutex_lock(&philo->table->fork_mutex[(philo->id + 1)
		% philo->table->nb_philo]);
	if (ft_print(philo, TAKE_FORK) == -1)
	{
		pthread_mutex_unlock(&philo->table->fork_mutex[philo->id]);
		pthread_mutex_unlock(&philo->table->fork_mutex[(philo->id + 1)
			% philo->table->nb_philo]);
		return (-1);
	}
	ft_philo_eat(philo);
	return (1);
}

void	*monitor(t_table *table)
{
	int		i;
	int		last_meal;

	i = 0;
	while (1)
	{
		if (i == table->nb_philo)
			i = 0;
		pthread_mutex_lock(&table->last_eat_mutex);
		last_meal = table->philo[i].last_eat;
		pthread_mutex_unlock(&table->last_eat_mutex);
		if (philo_get_time() - last_meal - table->start_time
			>= table->time_to_die)
		{
			ft_print(&table->philo[i], DIE);
			pthread_mutex_lock(&table->dead_mutex);
			table->dead = 1;
			pthread_mutex_unlock(&table->dead_mutex);
			return (NULL);
		}
		if (table->nb_eat != -1 && ft_eat_goal(table) == 1)
			return (NULL);
		i++;
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (1)
	{
		if (ft_check_dead_philo(philo->table))
			return (NULL);
		if (take_forks(philo) == -1)
			return (NULL);
	}
	return (NULL);
}
