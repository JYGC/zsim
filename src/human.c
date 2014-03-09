/*
 * human.c
 *
 *  Created on: Oct 14, 2013
 *      Author: Qiong Cai and Junying Chen
 */

#include "human.h"

struct cell human_new(
		int new_age,
		int new_health,
		bool gun){

	struct cell tmp_cell;

	srand(time(NULL));

	tmp_cell.age			= new_age;
	tmp_cell.health			= new_health;
	tmp_cell.gun_armed		= gun;
	tmp_cell.exposed		= false;
	tmp_cell.exposed_time	= 0;
	tmp_cell.infected		= false;

	return tmp_cell;
}

struct cell human_aging(struct cell source_cell){

	source_cell.age++;
	return source_cell;
}

struct cell human_tozombie(struct cell source_cell){

	if(
			source_cell.infected	== false &&
			source_cell.exposed		== true &&
			source_cell.exposed_time!= 0){

		source_cell.exposed_time--;

	}else if(
			source_cell.infected	== false &&
			source_cell.exposed		== true &&
			source_cell.exposed_time== 0){

		source_cell = zombie_new(
				source_cell.age,
				source_cell.health,
				source_cell.gun_armed);

	}

	return source_cell;
}

struct cell human_die(){

	struct cell tmp_cell = cell_makeempty();
	return tmp_cell;
}
