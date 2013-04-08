/*
 * main_declarations.h
 *
 *  Created on: 03-Apr-2013
 *      Author: aswin
 */
#include <pthread.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<time.h>

/*
 * This header file contains all the declarations that are used in the project
 */

#define MAX_USER 19 // Max No. of users - 20
#define MAX_PACKET 39 // Max No. of packets per user - 40
#define MAX_PACKET_TYPES 2 // We have used both text and video packets
#define PACKET_SIZE 40 // Setting the size of the packet

/*
 * The following structure declaration contains the packet format
 * userid - ID of the user to whom the packet is addressed to
 * payload - The data part of the packet
 * tt - Arrival time of the packet
 * type_of_data - Specifies whether the data is text or video
 * size - Gives the size of the payload content
 * encrypted_data - Used to hold the encrypted form of the payload
 */

struct packet_format
{
	int userid;
	char *payload;
	struct timeval tt;
	int type_of_data; //0-Text, 1-Video
	int size; //not sure how to fill this
	char *encrypted_data;
};

struct timeval tv;
typedef struct client_hdr {

	char packet[PACKET_SIZE];

} client_hdr;

/*
 * This structure declaration combines the packet format declaration along with
 * the total number of packets. This is later sent as arguments to the
 * different functions
 */

typedef struct packet_arg {
	struct packet_format *packets;
	int TotalPackets;
};


