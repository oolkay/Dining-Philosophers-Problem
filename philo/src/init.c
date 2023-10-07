/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:07:08 by omer/baha         #+#    #+#             */
/*   Updated: 2023/10/07 12:37:40 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/philo.h"

int	ft_check_dead_philo(t_table *table)
{
	int	flag;

	pthread_mutex_lock(&table->dead_mutex);
	flag = table->dead;
	pthread_mutex_unlock(&table->dead_mutex);
	if (flag == 1)
		return (1);
	return (0);
}

int	ft_init_table(t_table *table, int argc, char **argv)
{
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->start_time = philo_get_time();
	table->dead = 0;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->dead_mutex, NULL);
	pthread_mutex_init(&table->last_eat_mutex, NULL);
	pthread_mutex_init(&table->nb_eat_mutex, NULL);
	if (argc == 6)
		table->nb_eat = ft_atoi(argv[5]);
	else
		table->nb_eat = -1;
	table->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->nb_philo);
	if (!table->fork_mutex)
		return (-2);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philo)
	{
		free(table->fork_mutex);
		return (-2);
	}
	return (0);
}

int	ft_init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		table->philo[i].id = i;
		table->philo[i].nb_eat = 0;
		table->philo[i].last_eat = 0;
		table->philo[i].table = table;
		pthread_mutex_init(&table->fork_mutex[i], NULL);
		if (pthread_create(&table->philo[i].thread, NULL,
				&routine, &table->philo[i]) != 0)
			return (-2);
	}
	monitor(table);
	i = -1;
	while (++i < table->nb_philo)
		pthread_join(table->philo[i].thread, NULL);
	return (1);
}
