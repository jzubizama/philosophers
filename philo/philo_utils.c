/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:10:51 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/20 09:18:28 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	ft_print_change(char *str, t_philo *philo)
{
	size_t	t;

	t = get_current_time() - philo->init_time;
	pthread_mutex_lock(philo->dead_mut);
	if (!*(philo->dead))
		printf("%zu %i %s\n", t, philo->id + 1, str);
	pthread_mutex_unlock(philo->dead_mut);
}

void	ft_destroy_mut(t_philo	*philos, t_monitor *monit)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&monit->dead_mut);
	pthread_mutex_destroy(&monit->read_mut);
	while (i < philos->input.num_philo)
	{
		pthread_mutex_destroy(&philos[i].fork);
		i++;
	}
}
