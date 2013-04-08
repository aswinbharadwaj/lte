/*
 * pdcp.h
 *
 *  Created on: 03-Apr-2013
 *      Author: aswin
 */

/*
 * This file contains the static declarations needed
 * in the pdcp function and also contains the
 * function prototype
 */

#define PDCP_SIZE 100
#define ENCRYPT_SIZE 4



void *pdcp(struct packet_arg *packet_a);
