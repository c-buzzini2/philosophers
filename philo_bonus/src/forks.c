/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/31 15:35:56 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
//START HERE!!!! Fork processes, wait[id, graceful termination]

int	ft_parent(t_args *args, int last_pid)
{
	int		e_status;
	int		exited;
	//int		last_status;
	int		i;
	int		e_code;
	

	while (1)
	{
		waitpid(-1, &e_status, 0);
		// if (exited == last_pid)
		// 	last_status = estatus;
		if (exited <= 0)
			break ;
		if (WIFEXITED(e_status)) 
		{
    		e_code = WEXITSTATUS(e_status);
    		if (e_code == 2) 
			{
	        // send kill signals...
				return (2);
    		}
		}
	return (0);
	}
}

t_philo	*ft_create_philo(void)
{
	static t_philo	philo;

	return (&philo);
}

int	ft_forks(t_args *args)
{
	int		id;
	int		forks;
	t_philo	*philo;

	forks = 0;
	gettimeofday(&args->start_time, NULL);
	while (forks < args->nb_philo)
	{
		id = fork();
		if (id == -1)
		{
			perror("Error in the fork");
			exit(ft_free_destroy_return(1));
		}
		if (id == 0)
		{
			philo = ft_create_philo();
			philo->id = forks;
			ft_open_turn_sems(philo, args);
			ft_start_routine(philo);
		}
		forks++;
	}
	return (ft_parent(args, id));
}
