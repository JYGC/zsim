/*
 * cell_mesh.h
 *
 *  Created on: Oct 14, 2013
 *      Author: junying
 */

#ifndef MESH_H_
#define MESH_H_
#include "main.h"
#include "cell.h"

/* Functions for accessing mesh grids */
struct cell **mesh_newstencil(
		struct cell **,
		int,
		int,
		int,
		int);	/* Make new stencil from mesh */
void mesh_printmesh(struct cell ***,FILE *);		/* Print mesh to an output */
void mesh_printstat(int, struct cell ***,FILE *);
struct cell ***mesh_newblankworld();				/* Create new mesh with undefined elements */
struct cell ***mesh_populateworld();				/* Populate mesh with humans, zombies and free space */
void mesh_timestep(struct cell ***, int);	/* Evolution the mesh through time */
#endif /* MESH_H_ */
