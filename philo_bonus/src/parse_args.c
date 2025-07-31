/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:36:06 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/07/31 13:53:33 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		ft_puterror("You need 4 or 5 arguments");
		exit (1);
	}
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '+' || argv[i][j] == '-')
		{
			if (argv[i][j] == '-' || !argv[i][++j])
				return (1);
		}
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j++]) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_parse_args(t_args *args, int argc, char **argv)
{
	if (ft_check_args(argc, argv) == 1)
	{
		ft_puterror("Arguments must be positive numbers");
		exit (1);
	}
	args->nb_philo = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		args->should_eat = ft_atoi(argv[5]);
	return (0);
}
