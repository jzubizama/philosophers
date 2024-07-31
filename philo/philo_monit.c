/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:38:45 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/02 13:40:18 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	ft_check_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->input.num_philo)
	{
		pthread_mutex_lock(philos[i].read_mut);
		if (get_current_time() - philos[i].last_meal
			>= (size_t)philos[i].input.t_die)
		{
			pthread_mutex_unlock(philos[i].read_mut);
			ft_print_change("died", &philos[i]);
			pthread_mutex_lock(philos[i].dead_mut);
			*(philos[i].dead) = 1;
			pthread_mutex_unlock(philos[i].dead_mut);
			return (1);
		}
		pthread_mutex_unlock(philos[i].read_mut);
		i++;
	}
	return (0);
}

int	ft_check_meals(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos->input.num_times_eat < 0)
		return (0);
	while (i < philos->input.num_philo)
	{
		pthread_mutex_lock(philos[i].read_mut);
		if (philos[i].num_eaten < philos->input.num_times_eat)
		{
			pthread_mutex_unlock(philos[i].read_mut);
			return (0);
		}
		pthread_mutex_unlock(philos[i].read_mut);
		i++;
	}
	pthread_mutex_lock(philos[0].dead_mut);
	*(philos[0].dead) = 1;
	pthread_mutex_unlock(philos[0].dead_mut);
	return (1);
}

void	*ft_monit(void *monit)
{
	t_philo	*philos;

	philos = ((t_monitor *)monit)->philos;
	while (1)
	{
		if (ft_check_dead(philos) || ft_check_meals(philos))
			break ;
	}
	return (NULL);
}
