/*
 * human.h
 *
 *  Created on: Oct 14, 2013
 *      Author: Qiong Cai and Junying Chen
 */

#ifndef HUMAN_H_
#define HUMAN_H_
#include "main.h"
#include "cell.h"
#include "mesh.h"

struct cell human_new(int,int,bool);
struct cell human_tozombie(struct cell);
struct cell human_aging(struct cell);
struct cell human_die();
#endif /* HUMAN_H_ */
