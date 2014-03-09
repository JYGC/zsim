/*
 * cell.h
 *
 *  Created on: Oct 14, 2013
 *      Author: Qiong Cai and Junying Chen
 */

#ifndef CELL_H_
#define CELL_H_
#include "main.h"
#include "mesh.h"
#include "human.h"
#include "zombie.h"

/* Define struct which represents the
 * entities human, zombies and free
 * space */
struct cell{
	int		ownership;
	int		age;
	int		health;
	bool	gun_armed;
	bool	exposed;
	int		exposed_time;
	bool	infected;
};

/* Functions for accessing individual
 * cells. */
void cell_actionself(struct cell *,int);
void cell_actionothers(
		struct cell *,
		struct cell *,
		struct cell *,
		struct cell *,
		struct cell *);
void cell_move(struct cell *,struct cell *);		/* Move entity */
struct cell	cell_makeempty();						/* Turn cell into free space */
struct cell	cell_changeownership(struct cell,int);	/* Change which CPU owns the cell */


#endif /* CELL_H_ */
