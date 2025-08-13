/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/13 16:33:55 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_waiter_error(t_args *args, t_pids *pids)
{
	ft_kill_remaining_processes(pids, args);
	free(pids);
	ft_close_arr_sems();
	return (1);
}

void	ft_change_boolean(t_pids *pids, int exited, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pids[i].pid == exited)
		{
			pids[i].exited = true;
			break ;
		}
		i++;
	}
}

void	ft_kill_remaining_processes(t_pids *pids, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pids[i].exited == false)
			kill(pids[i].pid, SIGKILL);
		i++;
	}
}

int	ft_parent_2(t_args *args, t_pids *pids)
{
	pthread_mutex_lock(&args->waiter.waiter_mutex);
	args->waiter.kill_waiter = true;
	pthread_mutex_unlock(&args->waiter.waiter_mutex);
	sem_post(args->waiter_sem);
	sem_post(args->waiter_sem);
	pthread_join(args->waiter.w_thread, NULL);
	free(pids);
	ft_close_arr_sems();
	pthread_mutex_destroy(&args->waiter.waiter_mutex);
	sem_close(args->waiter_sem);
	return (0);
}

int	ft_parent(t_args *args, t_pids *pids)
{
	int		e_status;
	int		exited_pid;
	int		e_code;
	int		exited_count;

	exited_count = 0;
	while (exited_count < args->nb_philo)
	{
		exited_pid = waitpid(-1, &e_status, 0);
		if (exited_pid > 0)
		{
			exited_count++;
			ft_change_boolean(pids, exited_pid, args);
			if (WIFEXITED(e_status))
			{
				e_code = WEXITSTATUS(e_status);
				if (e_code == 2 || e_code == 3)
					ft_kill_remaining_processes(pids, args);
			}
		}
	}
	return (ft_parent_2(args, pids));
}
