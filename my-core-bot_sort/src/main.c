#include "../include/my_core_bot.h"
#include "structs.h"

void	ft_init_func(void *data);
void	ft_user_loop(void *data);
void 	worker_combine(t_obj *worker);

t_obj	**ft_get_warriors_sorted(t_obj **units, int order, int *war_count);
int	fight(t_obj	**our_warriors, int our_count, t_obj	**opponent_warriors, int opponent_count);

int	main(int argc, char **argv)
{
	int	won;

	// ft_enable_debug();
		// uncomment this to show more debug information in the console when running a game
	t_game_data *game_data = malloc(3 * sizeof(int));
	game_data->warriors_amount = 3;
	game_data->workers_amount = 0;
	game_data->wave_workers = 1;

	ft_init_con("hnataraj", &argc, argv);
	won = ft_loop(&ft_init_func, &ft_user_loop, NULL, game_data);
	// won = ft_loop(&ft_init_func, &ft_user_loop, NULL, NULL);
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

// this function is called every time new data is recieved
void	ft_user_loop(void *data)
{
	t_obj	**units;
	t_obj	*enemy_core;
	int		i;
	t_obj	*curr;
	int		amount_workers;
	int		amount_warriors;
	int		attack_core;

	units = ft_get_my_units();
	enemy_core = ft_get_first_opponent_core();

	i = 0;
	t_game_data *game_data = (t_game_data *)data;

	amount_workers = 0;
	amount_workers = 0;
	attack_core = 1;
	while (units[i]) 
	{
		curr = units[i];
		if (curr->s_unit.type_id == UNIT_WARRIOR) // if the unit is a warrior
		{
			amount_warriors++;
			t_obj *enemy = ft_get_nearest_opponent_unit(curr);
			if (enemy)
			{
				ft_travel_attack(curr, enemy);
				attack_core = -attack_core;
			}
			else
				ft_travel_attack(curr, enemy_core);
		}
		if (curr->s_unit.type_id == UNIT_WORKER)
		{
			amount_workers++;
			worker_combine(curr);
		}
		i++;
	}
	if (game_data->wave_workers)
	{

		if (ft_create_unit(UNIT_WORKER))
		{
			game_data->workers_amount++;
			game_data->wave_workers = 0;
		}
		if (ft_create_unit(UNIT_WORKER))
		{
			game_data->workers_amount++;
		}

		if (ft_create_unit(UNIT_WORKER))
		{
			game_data->workers_amount++;
		}
	}
	int wallet = ft_get_my_team()->balance;

	if (game_data->warriors_amount == 3 && wallet >=  game_data->warriors_amount * 750)
	{
		ft_create_unit(UNIT_WARRIOR);
		ft_create_unit(UNIT_WARRIOR);
		ft_create_unit(UNIT_WARRIOR);
		game_data->warriors_amount = 1;
		game_data->wave_workers = 1;
	} else
	if (game_data->warriors_amount == 1)
	{
		ft_create_unit(UNIT_WARRIOR);
	}

	
	free(units);
}

// this function is called every time new data is recieved
void	ft_user_loop2(void *data)
{
	t_obj	**units;
	// t_obj	*enemy_core;
	int		i;
	t_obj	*curr;
	int		amount_workers;
	int		amount_warriors;
	// int		attack_core;

	// (void)data;

	units = ft_get_my_units();
	// enemy_core = ft_get_first_opponent_core();

	i = 0;
	t_game_data *game_data = (t_game_data *)data;

	// t_obj	*warriors;
	// t_obj	*workers;

	

	amount_workers = 0;
	amount_warriors = 0;
	// attack_core = 1;
	while (units[i]) 
	{
		curr = units[i];
		if (curr->s_unit.type_id == UNIT_WARRIOR) // if the unit is a warrior
		{
			amount_warriors++;
			// t_obj *enemy = ft_get_nearest_opponent_unit(curr);
			// if (enemy)
			// {
			// 	ft_travel_attack(curr, enemy);
			// 	attack_core = -attack_core;
			// }
			// else
			// 	ft_travel_attack(curr, enemy_core);
		}
		if (curr->s_unit.type_id == UNIT_WORKER)
		{
			amount_workers++;
			worker_combine(curr);
		}
		i++;
	}

	t_obj	**my_warriors;
	t_obj	**opponent_warriors;
	// t_obj 	*my_core = ft_get_my_core();
	int	my_war_count;
	int	opponent_war_count;
	my_war_count = 0;
	opponent_war_count = 0;
	my_warriors = ft_get_warriors_sorted(units, -1, &my_war_count);

	// i = 0;
	// while (units[i]) 
	// {
	// 	printf("   uni       Id=%ld  i=%d  our_count =%d\n", units[i]->id, i, my_war_count);
	// 	i++;
	// }
	// i = 0;
	// printf("  -------------      my_war_count=%d   \n", my_war_count);
	// while (i < my_war_count) 
	// {
	// 	printf("   my  i=%d     Id=%ld    our_count =%d\n", i, my_warriors[i]->id, my_war_count);
	// 	// my_warriors++;
	// 	i++;
	// }

	// printf("Id=%ld    our_count =%d\n", curr->s_unit.type_id, my_war_count);
	// printf("after---> Id=%ld    our_count =%d\n", my_warriors[0].id, my_war_count);
	t_obj	**opponent_units = ft_get_opponent_units();

	opponent_warriors = ft_get_warriors_sorted(opponent_units, 1, &opponent_war_count);
	// i = 0;
	// printf("  -------------      opponent_war_count=%d   \n", opponent_war_count);
	// while (i < opponent_war_count) 
	// {
	// 	printf("   my  i=%d     Id=%ld    opponent_war_count =%d\n", i, opponent_warriors[i]->id, opponent_war_count);
	// 	// my_warriors++;
	// 	i++;
	// }
	// printf("fight=%d  %d\n", my_war_count, opponent_war_count);


	fight(my_warriors, my_war_count, opponent_warriors, opponent_war_count);


	free(my_warriors);
	free(opponent_warriors);

	// printf("======================\n");
	// printf("amount_warriors=%d\n", amount_warriors);
	if (game_data->wave_workers)
	{

		if (ft_create_unit(UNIT_WORKER))
		{
			game_data->workers_amount++;
			game_data->wave_workers = 0;
		}
		if (ft_create_unit(UNIT_WORKER))
		{
			game_data->workers_amount++;
		}

		if (ft_create_unit(UNIT_WORKER))
		{
			game_data->workers_amount++;
		}
	}
	int wallet = ft_get_my_team()->balance;

	if (game_data->warriors_amount == 3 && wallet >=  game_data->warriors_amount * 750)
	{
		ft_create_unit(UNIT_WARRIOR);
		ft_create_unit(UNIT_WARRIOR);
		ft_create_unit(UNIT_WARRIOR);
		game_data->warriors_amount = 1;
		game_data->wave_workers = 1;
	} else
	if (game_data->warriors_amount == 1)
	{
		ft_create_unit(UNIT_WARRIOR);
	}

	
	free(units);
	free(opponent_units);
}
