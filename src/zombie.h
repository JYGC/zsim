/*
 * zombie.h
 *
 *  Created on: Oct 14, 2013
 *      Author: Qiong Cai and Junying Chen
 */

#ifndef ZOMBIE_H_
#define ZOMBIE_H_
#include "main.h"
#include "cell.h"
#include "mesh.h"

#define ZOMBIE_DECAY_RATE	HOURS_IN_DAY*10
struct cell	zombie_new(int,int,bool);
struct cell	zombie_infect(struct cell);
struct cell	zombie_decay(struct cell);
struct cell	zombie_die();
#endif /* ZOMBIE_H_ */
