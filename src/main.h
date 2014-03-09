/*
 * main.h
 *
 *  Created on: Oct 14, 2013
 *      Author: Qiong Cai and Junying Chen
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Include all required header files. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "mpi.h"

/* Include file for openMP and MPI library */
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif /* OPENMP */

/* Define dimension of the world mesh
 * in which the simulation takes place. */
#define MESH_WIDTH	1000
#define MESH_HEIGHT	1500

#define PART_NUMBER	4

#define PART_WIDTH	(MESH_WIDTH)
#define PART_HEIGHT	(MESH_HEIGHT/PART_NUMBER)

#define PART_WIDTH_FRAME	((PART_WIDTH)+2)
#define PART_HEIGHT_FRAME	((PART_HEIGHT)+2)

/* Define time conversion factor, time
 * step and time limit. */
#define HOURS_IN_DAY	24
#define DAYS_IN_YEAR	365
#define DAYS			HOURS_IN_DAY
#define YEARS			DAYS*DAYS_IN_YEAR

#define TIME_STEP_HOUR	1
#define TIME_LIMIT		10

#ifndef AUXILLARY
#define AUXILLARY
int modulo(int,int);
void lock(int, bool *);
void unlock(int, bool *);
unsigned rand_ud();
#endif /* AUXILLARY */
#endif /* MAIN_H_ */

