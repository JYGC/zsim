/*
 * mesh.c
 *
 *  Created on: Oct 14, 2013
 *      Author: Qiong Cai and Junying Chen
 */

#include "mesh.h"

struct cell **mesh_newstencil(
		struct	cell **target_mesh,
		int		target_coord_j,
		int		target_coord_i,
		int		stencil_size_j,
		int		stencil_size_i){

	int	j, i;
	struct cell **stencil = malloc(stencil_size_j*sizeof(struct cell *));

	for(j=0; j<stencil_size_j; j++){
		stencil[j] = malloc(stencil_size_i*sizeof(struct cell));
	}

	for(
			j = target_coord_j-((stencil_size_j-1)/2);
			j <=target_coord_j+((stencil_size_j-1)/2);
			j++){

		for(
				i = target_coord_i-((stencil_size_i-1)/2);
				i <=target_coord_i+((stencil_size_i-1)/2);
				i++){

			stencil[j-(target_coord_j-((stencil_size_j-1)/2))]
			        [i-(target_coord_i-((stencil_size_i-1)/2))]
			         = target_mesh[modulo(j,MESH_HEIGHT)+1][modulo(i,MESH_WIDTH)+1];
		}
	}

	return stencil;
}

void mesh_printmesh(struct cell ***target_mesh, FILE *target_FILE){

	int n, j, i;

	for(n=0; n<PART_NUMBER; n++){

		for(j=1; j<PART_HEIGHT+1; j++){

			for(i=1; i<PART_WIDTH+1; i++){

				if(target_mesh[n][j][i].health != 0){
					if(
							target_mesh[n][j][i].exposed	== false &&
							target_mesh[n][j][i].infected	== false){

						fprintf(target_FILE,"H");

					}else if(
							target_mesh[n][j][i].exposed	== true &&
							target_mesh[n][j][i].infected	== false){

						fprintf(target_FILE,"E");

					}else if(
							target_mesh[n][j][i].infected	== true){

						fprintf(target_FILE,"Z");

					}
				}else{

					fprintf(target_FILE," ");
				}
			}

			putc('\n',target_FILE);
		}
	}
}

void mesh_printstat(int TIME, struct cell ***target_mesh, FILE *target_FILE){

	int n, j, i;

	int numH = 0;
	int numE = 0;
	int numZ = 0;

	for(n=0;n<PART_NUMBER;n++){

		for(j=1;j<PART_HEIGHT+1;j++){

			for(i=1;j<PART_WIDTH+1;i++){

				if(target_mesh[n][j][i].health != 0){
					if(
							target_mesh[n][j][i].exposed	== false &&
							target_mesh[n][j][i].infected	== false){

						numH++;

					}else if(
							target_mesh[n][j][i].exposed	== true &&
							target_mesh[n][j][i].infected	== false){

						numE++;

					}else if(
							target_mesh[n][j][i].infected	== true){

						numZ++;

					}
				}
			}
		}
	}

	fprintf(target_FILE,"%i %i %i %i\n", TIME, numH, numE, numZ);
}

struct cell ***mesh_newblankworld(){

	int n, j, i;
	struct cell ***tmp_mesh = (struct cell ***)malloc(PART_NUMBER*sizeof(struct cell **));

	for(n=0; n<PART_NUMBER; n++){

		tmp_mesh[n] = (struct cell **)malloc(PART_HEIGHT_FRAME*sizeof(struct cell *));

		#pragma omp parallel private(j, i)
		for(j=0;j<PART_HEIGHT_FRAME;j++){

			tmp_mesh[n][j] = (struct cell *)malloc(PART_WIDTH_FRAME*sizeof(struct cell));

			for(i=0;i<PART_WIDTH_FRAME;i++){
				tmp_mesh[n][j][i] = cell_makeempty();
			}
		}
	}

	return tmp_mesh;
}

struct cell ***mesh_populateworld(){

	int n, j, i;
	struct cell ***tmp_mesh;

	tmp_mesh = mesh_newblankworld();

	srand(time(NULL));
	srand48((long)rand());

	int p0j = rand();
	int p0i = rand();

	tmp_mesh[0]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i,PART_WIDTH)+1]
	          = zombie_new(35,100,false);
	tmp_mesh[0]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i,PART_WIDTH)+2]
	          = zombie_new(35,100,false);
	tmp_mesh[0]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i,PART_WIDTH)+3]
	          = zombie_new(35,100,false);
	tmp_mesh[0]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i,PART_WIDTH)+4]
	          = zombie_new(35,100,false);
	tmp_mesh[0]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i,PART_WIDTH)+5]
	          = zombie_new(35,100,false);
	tmp_mesh[1]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+1]
	          = zombie_new(35,100,false);
	tmp_mesh[1]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+2]
	          = zombie_new(35,100,false);
	tmp_mesh[1]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+3]
	          = zombie_new(35,100,false);
	tmp_mesh[1]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+4]
	          = zombie_new(35,100,false);
	tmp_mesh[1]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+5]
	          = zombie_new(35,100,false);
	tmp_mesh[2]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+1]
	          = zombie_new(35,100,false);
	tmp_mesh[2]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+2]
	          = zombie_new(35,100,false);
	tmp_mesh[2]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+3]
	          = zombie_new(35,100,false);
	tmp_mesh[2]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+4]
	          = zombie_new(35,100,false);
	tmp_mesh[2]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+5]
	          = zombie_new(35,100,false);
	tmp_mesh[3]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+1]
	          = zombie_new(35,100,false);
	tmp_mesh[3]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+2]
	          = zombie_new(35,100,false);
	tmp_mesh[3]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+3]
	          = zombie_new(35,100,false);
	tmp_mesh[3]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+4]
	          = zombie_new(35,100,false);
	tmp_mesh[3]
	         [modulo(p0j,PART_HEIGHT)+1]
	         [modulo(p0i-1,PART_WIDTH)+5]
	          = zombie_new(35,100,false);

	for(n=0;n<PART_NUMBER;n++){

		#pragma omp parallel private(j, i)
		for(j=1;j<PART_HEIGHT;j++){

			for(i=1;i<PART_WIDTH;i++){

				if(drand48()<0.05){

					if(tmp_mesh[n][j][i].health == 0){
						tmp_mesh[n][j][i] = human_new((rand()%50)+10,100,false);
					}
				}
			}
		}
	}

	return tmp_mesh;
}

/*
 * Parallelised and multithreaded mesh_timestep function */
void mesh_timestep(struct cell ***source_mesh, int TIME){

	int size;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status status;

	int j, i;
	bool locks_height[PART_HEIGHT_FRAME];
	double randnum;

	MPI_Datatype cellDatatype;
	MPI_Type_contiguous(sizeof(struct cell), MPI_BYTE, &cellDatatype);
	MPI_Type_commit(&cellDatatype);

	MPI_Datatype hghost;
	MPI_Type_contiguous(
			PART_WIDTH,
			cellDatatype,
			&hghost);
	MPI_Type_commit(&hghost);

	MPI_Datatype vghost;
	MPI_Type_vector(
			PART_HEIGHT,
			1,
			PART_WIDTH*4,
			cellDatatype,
			&vghost);
	MPI_Type_commit(&vghost);


	for(j = 0; j < PART_HEIGHT_FRAME; j++) {locks_height[j] = false;}

	srand(time(NULL));
	srand48((long)rand());

	/************** MPI Communications ****************/
	if(rank==0){
		MPI_Send(&source_mesh[0][PART_HEIGHT][1],1,hghost,1,1, MPI_COMM_WORLD);
		MPI_Recv(&source_mesh[0][PART_HEIGHT+1][1],1,hghost,1,1, MPI_COMM_WORLD,&status);
	}else if(rank==1){
		MPI_Recv(&source_mesh[1][0][1],1,hghost,0,1, MPI_COMM_WORLD,&status);
		MPI_Send(&source_mesh[1][1][1],1,hghost,0,1, MPI_COMM_WORLD);
	}else if(rank==2){
		MPI_Send(&source_mesh[2][PART_HEIGHT][1],1,hghost,3,1, MPI_COMM_WORLD);
		MPI_Recv(&source_mesh[2][PART_HEIGHT+1][1],1,hghost,3,1, MPI_COMM_WORLD,&status);
	}else if(rank==3){
		MPI_Recv(&source_mesh[3][0][1],1,hghost,2,1, MPI_COMM_WORLD,&status);
		MPI_Send(&source_mesh[3][1][1],1,hghost,2,1, MPI_COMM_WORLD);
	}

	if(rank==0){
		MPI_Recv(&source_mesh[0][0][1],1,hghost,3,1, MPI_COMM_WORLD,&status);
		MPI_Send(&source_mesh[0][1][1],1,hghost,3,1, MPI_COMM_WORLD);
	}else if(rank==1){
		MPI_Send(&source_mesh[1][PART_HEIGHT][1],1,hghost,2,1, MPI_COMM_WORLD);
		MPI_Recv(&source_mesh[1][PART_HEIGHT+1][1],1,hghost,2,1, MPI_COMM_WORLD,&status);
	}else if(rank==2){
		MPI_Recv(&source_mesh[2][0][1],1,hghost,1,1, MPI_COMM_WORLD,&status);
		MPI_Send(&source_mesh[2][1][1],1,hghost,1,1, MPI_COMM_WORLD);
	}else if(rank==3){
		MPI_Send(&source_mesh[3][PART_HEIGHT][1],1,hghost,0,1, MPI_COMM_WORLD);
		MPI_Recv(&source_mesh[3][PART_HEIGHT+1][1],1,hghost,0,1, MPI_COMM_WORLD,&status);
	}
	/***************************************************/


	if(rank==0){

		#pragma omp parallel default(none) shared(source_mesh,locks_height,randnum,TIME,rank) private(j, i)
		for(j = 1; j < PART_HEIGHT+1; j++){
			lock(j,locks_height);
			for(i = 1; i < PART_WIDTH+1; i++){

				if(source_mesh[rank][j][i].health != 0){

					cell_actionself(&source_mesh[rank][j][i],TIME);

					randnum = drand48();

					if(
							randnum >=0.00 &&
							randnum < 0.25){

						if(source_mesh[rank][j+1][i].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j+1][i]);

						}else if(source_mesh[rank][j+1][i].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j-1][i],
									&source_mesh[rank][j][i+1]);

						}

					}else if(
							randnum >=0.25 &&
							randnum < 0.50){

						if(source_mesh[rank][j][i+1].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i+1]);

						}else if(source_mesh[rank][j][i+1].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i+1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j-1][i]);

						}

					}else if(
							randnum >=0.50 &&
							randnum < 0.75){

						if(source_mesh[rank][j-1][i].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i]);

						}else if(source_mesh[rank][j-1][i].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j-1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i+1]);

						}

					}else if(
							randnum >=0.75 &&
							randnum < 1.00){
						if(source_mesh[rank][j][i-1].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i-1]);

						}else if(source_mesh[rank][j][i-1].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i+1],
									&source_mesh[rank][j-1][i]);

						}
					}
				}
			}
			unlock(j,locks_height);
		}

		//Print rank 0 partition
		printf("*******Print rank 0 partition*********\n");
		for(j = 1; j < PART_HEIGHT+1; j++){

			for(i = 1; i < PART_WIDTH+1; i++){
				if(source_mesh[rank][j][i].health != 0){
					if(
							source_mesh[rank][j][i].exposed	== false &&
							source_mesh[rank][j][i].infected	== false){

						fprintf(stdout,"H");

					}else if(
							source_mesh[rank][j][i].exposed	== true &&
							source_mesh[rank][j][i].infected	== false){

						fprintf(stdout,"E");

					}else if(
							source_mesh[rank][j][i].infected	== true){

						fprintf(stdout,"Z");

					}
				}else{

					fprintf(stdout,"%i",rank);
				}
			}
			printf("\n");
		}

	}else if(rank==1){

		#pragma omp parallel default(none) shared(source_mesh,locks_height,randnum,TIME,rank) private(j, i)
		for(j = 1; j < PART_HEIGHT+1; j++){
			lock(j,locks_height);
			for(i = 1; i < PART_WIDTH+1; i++){

				if(source_mesh[rank][j][i].health != 0){

					cell_actionself(&source_mesh[rank][j][i],TIME);

					randnum = drand48();

					if(
							randnum >=0.00 &&
							randnum < 0.25){

						if(source_mesh[rank][j+1][i].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j+1][i]);

						}else if(source_mesh[rank][j+1][i].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j-1][i],
									&source_mesh[rank][j][i+1]);

						}

					}else if(
							randnum >=0.25 &&
							randnum < 0.50){

						if(source_mesh[rank][j][i+1].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i+1]);

						}else if(source_mesh[rank][j][i+1].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i+1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j-1][i]);

						}

					}else if(
							randnum >=0.50 &&
							randnum < 0.75){

						if(source_mesh[rank][j-1][i].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i]);

						}else if(source_mesh[rank][j-1][i].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j-1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i+1]);

						}

					}else if(
							randnum >=0.75 &&
							randnum < 1.00){
						if(source_mesh[rank][j][i-1].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i-1]);

						}else if(source_mesh[rank][j][i-1].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i+1],
									&source_mesh[rank][j-1][i]);

						}
					}
				}
			}
			unlock(j,locks_height);
		}
		//Print rank 0 partition
		printf("*******Print rank 1 partition*********\n");
		for(j = 1; j < PART_HEIGHT+1; j++){

			for(i = 1; i < PART_WIDTH+1; i++){
				if(source_mesh[rank][j][i].health != 0){
					if(
							source_mesh[rank][j][i].exposed	== false &&
							source_mesh[rank][j][i].infected	== false){

						fprintf(stdout,"H");

					}else if(
							source_mesh[rank][j][i].exposed	== true &&
							source_mesh[rank][j][i].infected	== false){

						fprintf(stdout,"E");

					}else if(
							source_mesh[rank][j][i].infected	== true){

						fprintf(stdout,"Z");

					}
				}else{

					fprintf(stdout,"%i",rank);
				}
			}
			printf("\n");
		}
	}else if(rank==2){

		#pragma omp parallel default(none) shared(source_mesh,locks_height,randnum,TIME,rank) private(j, i)
		for(j = 1; j < PART_HEIGHT+1; j++){
			lock(j,locks_height);
			for(i = 1; i < PART_WIDTH+1; i++){

				if(source_mesh[rank][j][i].health != 0){

					cell_actionself(&source_mesh[rank][j][i],TIME);

					randnum = drand48();

					if(
							randnum >=0.00 &&
							randnum < 0.25){

						if(source_mesh[rank][j+1][i].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j+1][i]);

						}else if(source_mesh[rank][j+1][i].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j-1][i],
									&source_mesh[rank][j][i+1]);

						}

					}else if(
							randnum >=0.25 &&
							randnum < 0.50){

						if(source_mesh[rank][j][i+1].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i+1]);

						}else if(source_mesh[rank][j][i+1].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i+1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j-1][i]);

						}

					}else if(
							randnum >=0.50 &&
							randnum < 0.75){

						if(source_mesh[rank][j-1][i].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i]);

						}else if(source_mesh[rank][j-1][i].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j-1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i+1]);

						}

					}else if(
							randnum >=0.75 &&
							randnum < 1.00){
						if(source_mesh[rank][j][i-1].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i-1]);

						}else if(source_mesh[rank][j][i-1].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i+1],
									&source_mesh[rank][j-1][i]);

						}
					}
				}
			}
			unlock(j,locks_height);
		}
		//Print rank 2 partition
		printf("*******Print rank 0 partition*********\n");
		for(j = 1; j < PART_HEIGHT+1; j++){

			for(i = 1; i < PART_WIDTH+1; i++){
				if(source_mesh[rank][j][i].health != 0){
					if(
							source_mesh[rank][j][i].exposed	== false &&
							source_mesh[rank][j][i].infected	== false){

						fprintf(stdout,"H");

					}else if(
							source_mesh[rank][j][i].exposed	== true &&
							source_mesh[rank][j][i].infected	== false){

						fprintf(stdout,"E");

					}else if(
							source_mesh[rank][j][i].infected	== true){

						fprintf(stdout,"Z");

					}
				}else{

					fprintf(stdout,"%i",rank);
				}
			}
			printf("\n");
		}
	}else if(rank==3){
		#pragma omp parallel default(none) shared(source_mesh,locks_height,randnum,TIME,rank) private(j, i)
		for(j = 1; j < PART_HEIGHT+1; j++){
			lock(j,locks_height);
			for(i = 1; i < PART_WIDTH+1; i++){

				if(source_mesh[rank][j][i].health != 0){

					cell_actionself(&source_mesh[rank][j][i],TIME);

					randnum = drand48();

					if(
							randnum >=0.00 &&
							randnum < 0.25){

						if(source_mesh[rank][j+1][i].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j+1][i]);

						}else if(source_mesh[rank][j+1][i].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j-1][i],
									&source_mesh[rank][j][i+1]);

						}

					}else if(
							randnum >=0.25 &&
							randnum < 0.50){

						if(source_mesh[rank][j][i+1].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i+1]);

						}else if(source_mesh[rank][j][i+1].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i+1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j-1][i]);

						}

					}else if(
							randnum >=0.50 &&
							randnum < 0.75){

						if(source_mesh[rank][j-1][i].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i]);

						}else if(source_mesh[rank][j-1][i].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j-1][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i+1]);

						}

					}else if(
							randnum >=0.75 &&
							randnum < 1.00){
						if(source_mesh[rank][j][i-1].health == 0){

							cell_move(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i-1]);

						}else if(source_mesh[rank][j][i-1].health != 0){

							cell_actionothers(
									&source_mesh[rank][j][i],
									&source_mesh[rank][j][i-1],
									&source_mesh[rank][j+1][i],
									&source_mesh[rank][j][i+1],
									&source_mesh[rank][j-1][i]);

						}
					}
				}
			}
			unlock(j,locks_height);
		}
		//Print rank 3 partition
		printf("*******Print rank 0 partition*********\n");
		for(j = 1; j < PART_HEIGHT+1; j++){

			for(i = 1; i < PART_WIDTH+1; i++){
				if(source_mesh[rank][j][i].health != 0){
					if(
							source_mesh[rank][j][i].exposed	== false &&
							source_mesh[rank][j][i].infected	== false){

						fprintf(stdout,"H");

					}else if(
							source_mesh[rank][j][i].exposed	== true &&
							source_mesh[rank][j][i].infected	== false){

						fprintf(stdout,"E");

					}else if(
							source_mesh[rank][j][i].infected	== true){

						fprintf(stdout,"Z");

					}
				}else{

					fprintf(stdout,"%i",rank);
				}
			}
			printf("\n");
		}
	}
}
