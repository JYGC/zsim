/*
 * zombie.c
 *
 *  Created on: Oct 14, 2013
 *      Author: Qiong Cai and Junying Chen
 */

#include "zombie.h"

/************* ZOMBIE *************/
struct cell zombie_new(
		int new_age,
		int new_health,
		bool gun){

	struct cell tmp_cell;

	tmp_cell.age			= new_age;
	tmp_cell.health			= new_health;
	tmp_cell.gun_armed		= gun;
	tmp_cell.exposed		= false;
	tmp_cell.exposed_time	= 0;
	tmp_cell.infected		= true;

	return tmp_cell;
}

struct cell zombie_infect(struct cell target_cell){

	target_cell.exposed		= true;
	target_cell.exposed_time= 5;
	target_cell.health		-=10;

	return target_cell;
}

struct cell zombie_decay(struct cell self_cell){

	self_cell.health--;

	return self_cell;
}

struct cell zombie_die(){

	struct cell tmp_cell = cell_makeempty();
	return tmp_cell;
}

