/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:10:51 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/20 09:56:42 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philobonus.h"

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
	sem_wait(philo->input->sem_dead);
	if (!(philo->dead))
		printf("%zu %i %s\n", t, philo->id + 1, str);
	sem_post(philo->input->sem_dead);
}

void	ft_destroy_sem(t_input *in)
{
	int	i;

	i = 0;
	sem_close(in->sem_fork);
	sem_close(in->sem_dead);
	sem_close(in->sem_read);
	sem_close(in->sem_meal);
	sem_close(in->sem_print);
}
