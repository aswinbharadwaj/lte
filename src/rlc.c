/*
 * rlc.c
 *
 *  Created on: 04-Apr-2013
 *      Author: aswin
 */

#include "main_declarations.h"
#include "rlc.h"

#include "lte_component_provider.h"

/*
 * This is the rlc function which receives as input a packet
 * and the total number of packets together
 * in a structure. It decomposes them and uses them
 * individually to apply segmentation for each packet that
 * was received in the program. It then stores the
 * segmented data into the output file.
 */

void *rlc(struct packet_arg *packet_a)
{


	FILE *fp;
	struct packet_format *packets = (*packet_a).packets;
	int TotalPackets = (*packet_a).TotalPackets;
	fp = fopen("output.txt", "w");

	int NoOfUsers=1,i,k,size;

	if(packets[1].userid==1)
		NoOfUsers=1;
	else
	{
		for(i=1;i<TotalPackets;i++)
		{
			if(packets[i].userid < packets[i-1].userid)
				break;
			else
				NoOfUsers++;
		}
	}

	//printf("\n\nIn RLC - No of Users = %d", NoOfUsers);

	int *NoOfPackets;
	NoOfPackets = (int *)malloc(sizeof(int)*NoOfUsers);

	int *SequenceNumber;
	SequenceNumber = (int *)malloc(sizeof(int)*NoOfUsers);

	int *index;
	index = (int *)malloc(sizeof(int)*NoOfUsers);

	for(i=0;i<NoOfUsers;i++)
		SequenceNumber[i]=0;

	for(i=0;i<NoOfUsers;i++)
		index[i]=0;

	for(i=0;i<TotalPackets;i++)
		NoOfPackets[packets[i].userid-1]++;

	/*
	printf("\nIn RLC - No of Packets per user : ");
	for(i=0;i<NoOfUsers;i++)
	printf("\n%d - %d", i+1, NoOfPackets[i]);
	*/

	char **buffer = (char **)malloc(sizeof(char*)*NoOfUsers);

	for(i=0;i<NoOfUsers;i++)
		buffer[i]=(char *)malloc(sizeof(char)*RLC_SIZE);

	printf("\n\n*** After RLC :\n\n\tUser ID\tSequence Number\tContent\n");
	fprintf(fp, "User ID\tSequence Number\tContent\n");

	for(i=0;i<TotalPackets;i++)
	{
		size = strlen(packets[i].encrypted_data);
		//printf("\n\nSize of this packet = %d, Content = %s", size, packets[i].encrypted_data);

		for(k=0;k<size;)
		{
			//printf("\nbefore = %s, index = %d", buffer[packets[i].userid-1], index[packets[i].userid-1]);

			buffer[packets[i].userid-1][index[packets[i].userid-1]++] = packets[i].encrypted_data[k++];

			//printf(", user id = %d, buffer = %s", packets[i].userid, buffer[packets[i].userid-1]);

			if( strlen(buffer[packets[i].userid-1]) == RLC_SIZE)
			{
				SequenceNumber[packets[i].userid-1]++;

				printf("\n\t%d\t%d\t\t%s", packets[i].userid,SequenceNumber[packets[i].userid-1], buffer[packets[i].userid-1]);
				tracepoint(lte_component, rlc_packet, "RLC", packets[i].userid, SequenceNumber[packets[i].userid-1], buffer[packets[i].userid-1]);
				fprintf(fp, "\n%d\t%d\t\t%s", packets[i].userid,SequenceNumber[packets[i].userid-1], buffer[packets[i].userid-1]);

				//printf("\nUser ID = %d, Sequence Number = %d, Buffer = %s\n", packets[i].userid, SequenceNumber[packets[i].userid-1], buffer[packets[i].userid-1]);

				index[packets[i].userid-1]=0;

				memset(buffer[packets[i].userid-1], '\0', 2*sizeof(buffer[packets[i].userid-1]) );
			}

		}
	}

	for(i=0;i<NoOfUsers;i++)
	{
		if(strlen (buffer[i]) !=0)
		{
			SequenceNumber[i]++;
			printf("\n\t%d\t%d\t\t%s", i+1, SequenceNumber[i], buffer[i]);
			tracepoint(lte_component, rlc_packet, "RLC", i+1, SequenceNumber[i], buffer[i]);

			fprintf(fp, "\n%d\t%d\t\t%s", i+1, SequenceNumber[i], buffer[i]);

			//printf("\nUSER ID = %d, Sequence Number = %d, Buffer = %s\n", i+1, SequenceNumber[i], buffer[i]);
		}
	}

	fclose(fp);

}


