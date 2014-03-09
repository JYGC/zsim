/*
 * main.c
 *
 *  Created on: Oct 14, 2013
 *      Author: Qiong Cai and Junying Chen
 */

#include "main.h"
#include "cell.h"
#include "mesh.h"
#include "human.h"
#include "zombie.h"

int main(int argc, char *argv[]){

	int time_hour;
	struct cell ***world_mesh;
	/* The reason "struct cell **world_mesh" instead of
	 * "struct cell world_mesh[MESH_HEIGHT][MESH_WIDTH]"
	 * is that the latter caused a stack overflow to
	 * occur when ever the project executes. As a result,
	 * "world_mesh" can only be stored in heap memory
	 * using dynamic memory allocation via the "malloc"
	 * function. */

	world_mesh = mesh_populateworld();	/* Create humans and zombies on world mesh */

	//mesh_printmesh(world_mesh,stdout);
	printf("************************************\n");

	#ifdef _OPENMP
	double start_time = omp_get_wtime();
	#endif

	MPI_Init(NULL,NULL);

	for(time_hour = 0; time_hour <= TIME_LIMIT; time_hour++){

		mesh_timestep(
				world_mesh,
				time_hour);
	}

	MPI_Finalize();

	mesh_printmesh(world_mesh,stdout);

	#ifdef _OPENMP
	fprintf(stdout,"%i\t%f\n",omp_get_max_threads(),omp_get_wtime()-start_time);
	#endif

	free(world_mesh);
	exit(0);
}
