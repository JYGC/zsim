/*
 * cell.c
 *
 *  Created on: Oct 14, 2013
 *      Author: Qiong Cai and Junying Chen
 */

#include "cell.h"

void cell_move(
		struct cell *orig_cell,
		struct cell *dest_cell){

	*dest_cell = *orig_cell;
	*orig_cell = cell_makeempty();
}

void cell_actionself(struct cell *source_cell, int TIME){

	if(source_cell->health != 0){

		/* If human */
		if(
				source_cell->infected== false &&
				source_cell->exposed == false){

			if(
					TIME			!= 0 &&
					TIME%YEARS		== 0 &&
					source_cell->age < 60){
				*source_cell = human_aging(*source_cell);
			}else if(
					TIME			!= 0 &&
					TIME%YEARS		== 0 &&
					source_cell->age== 60){
				*source_cell = human_die();
			}

		/* If exposed */
		}else if(
				source_cell->infected== false &&
				source_cell->exposed == true){

			if(
					TIME			!= 0 &&
					TIME%YEARS		== 0 &&
					source_cell->age < 60){
				*source_cell = human_aging(*source_cell);
			}else if(
					TIME			!= 0 &&
					TIME%YEARS		== 0 &&
					source_cell->age== 60){
				*source_cell = human_die();
			}

			*source_cell = human_tozombie(*source_cell);

		/* If zombie */
		}else if(
				source_cell->infected== true){
			*source_cell = zombie_decay(*source_cell);

			if(source_cell->health==0){
				*source_cell = zombie_die();}

		}
	}
}

void cell_actionothers(
		struct cell *source_cell,
		struct cell *target_cell,
		struct cell *tange1_cell,
		struct cell *tange2_cell,
		struct cell *tange3_cell){

	if(
			source_cell->health		!= 0 &&
			source_cell->infected	== true){

		/* If zombie runs to human */
		if(target_cell->infected == false){
			*target_cell = zombie_infect(*target_cell);}

	}else if(
			source_cell->health		!= 0 &&
			source_cell->infected	== false){

		/* If human runs into zombie */
		if(target_cell->infected == true){
			*source_cell = zombie_infect(*source_cell);}

		/* Two humans meet */
		if(target_cell->infected == false){

			srand(time(NULL));
			srand48((long)rand());
			int doubleran = drand48();

			if(doubleran > 0 && doubleran < 0.1){
				if(tange1_cell->health == 0){
					*tange1_cell = human_new(0,100,false);
				}else if(tange2_cell->health == 0){
					*tange2_cell = human_new(0,100,false);
				}else if(tange3_cell->health == 0){
					*tange3_cell = human_new(0,100,false);
				}
			}
		}

	}
}

struct cell cell_makeempty(){

	struct cell tmp_cell;

	tmp_cell.age			= 0;
	tmp_cell.health			= 0;
	tmp_cell.gun_armed		= false;
	tmp_cell.exposed		= false;
	tmp_cell.exposed_time	= 0;
	tmp_cell.infected		= false;

	return tmp_cell;
}

struct cell cell_changeownership(
		struct	cell target_cell,
		int 	new_owner){

	struct cell tmp_cell= target_cell;

	tmp_cell.ownership	= new_owner;
	return tmp_cell;
}
