/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnataraj <hnataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:56:52 by hnataraj          #+#    #+#             */
/*   Updated: 2025/05/19 15:30:52 by hnataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/my_core_bot.h"
#include "structs.h"

void	ft_init_func(void *data);
void	ft_user_loop(void *data);
void	worker_combine(t_obj *worker);


int	main(int argc, char **argv)
{
	int			won;
	t_game_data	*game_data;

	game_data = malloc(3 * sizeof(int));
	game_data->warriors_amount = 3;
	game_data->workers_amount = 0;
	game_data->wave_workers = 1;
	ft_init_con("hnataraj", &argc, argv);
	won = ft_loop(&ft_init_func, &ft_user_loop, NULL, game_data);
	ft_close_con();
	if (won)
		return (0);
	return (1);
}

// this function is called once at the start of the game
void	ft_init_func(void *data)
{
	(void)data;
	printf("Init CORE Bot\n");
}

void	one_day(t_obj **units, int *amount_workers, int *amount_warriors)
{
	int		i;
	t_obj	*curr;
	t_obj	*enemy;

	i = 0;
	while (units[i])
	{
		curr = units[i];
		if (curr->s_unit.type_id == UNIT_WARRIOR)
		{
			*amount_warriors = *amount_warriors + 1;
			enemy = ft_get_nearest_opponent_unit(curr);
			if (enemy)
				ft_travel_attack(curr, enemy);
			else
				ft_travel_attack(curr, ft_get_first_opponent_core());
		}
		if (curr->s_unit.type_id == UNIT_WORKER)
		{
			*amount_workers = *amount_workers + 1;
			worker_combine(curr);
		}
		i++;
	}
}

void	create_warriors(t_game_data *game_data)
{
	int	wallet;

	wallet = ft_get_my_team()->balance;
	if (game_data->warriors_amount == 3 && wallet >= game_data->warriors_amount
		* 750)
	{
		ft_create_unit(UNIT_WARRIOR);
		ft_create_unit(UNIT_WARRIOR);
		ft_create_unit(UNIT_WARRIOR);
		game_data->warriors_amount = 1;
		game_data->wave_workers = 1;
	}
	else if (game_data->warriors_amount == 1)
	{
		ft_create_unit(UNIT_WARRIOR);
	}
}

// this function is called every time new data is recieved
void	ft_user_loop(void *data)
{
	t_obj		**units;
	int			amount_workers;
	int			amount_warriors;
	t_game_data	*game_data;

	units = ft_get_my_units();
	game_data = (t_game_data *)data;
	amount_workers = 0;
	amount_workers = 0;
	one_day(units, &amount_workers, &amount_warriors);
	if (game_data->wave_workers)
	{
		if (ft_create_unit(UNIT_WORKER))
		{
			game_data->workers_amount++;
			game_data->wave_workers = 0;
		}
		if (ft_create_unit(UNIT_WORKER))
			game_data->workers_amount++;
		if (ft_create_unit(UNIT_WORKER))
			game_data->workers_amount++;
	}
	create_warriors(game_data);
	free(units);
}
